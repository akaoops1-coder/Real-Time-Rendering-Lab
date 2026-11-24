#include "URBMetadata.h"
#include "URBTestPreset.h"
#include "Camera/CameraActor.h"
#include "Camera/CameraComponent.h"
#include "EngineUtils.h"
#include "HAL/FileManager.h"
#include "HAL/IConsoleManager.h"
#include "Interfaces/IPluginManager.h"
#include "Modules/ModuleManager.h"
#include "Misc/FileHelper.h"
#include "Misc/Paths.h"
#include "Misc/EngineVersion.h"
#include "RHI.h"
#include "DynamicRHI.h"
#include "Dom/JsonObject.h"
#include "Serialization/JsonSerializer.h"
#include "Serialization/JsonWriter.h"
#if PLATFORM_WINDOWS
#include "Windows/WindowsHWrapper.h"
#include <bcrypt.h>
#endif

static FString URBHashBytes(const void* Data,uint32 Size) {
#if PLATFORM_WINDOWS
 uint8 Hash[32]={},Empty=0; const uint8* Input=Size?static_cast<const uint8*>(Data):&Empty;
 if(BCryptHash(BCRYPT_SHA256_ALG_HANDLE,nullptr,0,const_cast<uint8*>(Input),Size,Hash,32)<0) return TEXT("");
 static const TCHAR Hex[]=TEXT("0123456789abcdef"); FString Result; Result.Reserve(64);
 for(uint8 Byte:Hash) { Result.AppendChar(Hex[Byte>>4]); Result.AppendChar(Hex[Byte&15]); } return Result;
#else
 return TEXT(""); // V1 runtime provenance is verified for Windows only.
#endif
}
FString FURBMetadata::SHA256(const TArray<uint8>& Bytes) { return URBHashBytes(Bytes.GetData(),Bytes.Num()); }
FString FURBMetadata::SHA256Text(const FString& Text) { FTCHARToUTF8 Utf8(*Text); return URBHashBytes(Utf8.Get(),Utf8.Length()); }
FString FURBMetadata::FileSHA256(const FString& Path) { TArray<uint8> Bytes; return FFileHelper::LoadFileToArray(Bytes,*Path)?SHA256(Bytes):TEXT(""); }
FString FURBMetadata::Json(const TSharedRef<FJsonObject>& Object) { FString Text; FJsonSerializer::Serialize(Object,TJsonWriterFactory<TCHAR,TCondensedJsonPrintPolicy<TCHAR>>::Create(&Text)); return Text; }
FString FURBMetadata::ContentSHA256(TSharedPtr<FJsonObject> Index) {
 if(SHA256Text(TEXT("abc"))!=TEXT("ba7816bf8f01cfea414140de5dae2223b00361a396177a9cb410ff61f20015ad")) { UE_LOG(LogTemp,Error,TEXT("URB SHA256 known-vector verification failed")); return TEXT(""); }
 TMap<FString,FString> Files;
 const auto AddRoot=[&Files](const FString& Root,const FString& Label) {
  TArray<FString> Found; IFileManager::Get().FindFilesRecursive(Found,*Root,TEXT("*"),true,false);
  for(const auto& File:Found) { FString Relative=File; FPaths::MakePathRelativeTo(Relative,*(Root/TEXT(""))); Files.Add(Label+TEXT("/")+Relative,File); }
 };
 AddRoot(FPaths::ConvertRelativePathToFull(FPaths::ProjectContentDir()),TEXT("Project/Content"));
 AddRoot(FPaths::ConvertRelativePathToFull(FPaths::ProjectConfigDir()),TEXT("Project/Config"));
 const auto Plugin=IPluginManager::Get().FindPlugin(TEXT("URBenchmark"));
 if(!Plugin) return TEXT("");
 AddRoot(FPaths::ConvertRelativePathToFull(Plugin->GetContentDir()),TEXT("URBenchmark/Content"));
 Files.Add(TEXT("Project/Project.uproject"),FPaths::GetProjectFilePath());
 TArray<FString> Names; Files.GetKeys(Names); Names.Sort();
 FString Combined; TArray<TSharedPtr<FJsonValue>> Entries;
 for(const auto& Name:Names) { const FString Hash=FileSHA256(Files[Name]); if(Hash.IsEmpty()) return TEXT(""); Combined+=Name+TEXT("|")+Hash+TEXT("\n"); auto Entry=MakeShared<FJsonObject>(); Entry->SetStringField(TEXT("path"),Name); Entry->SetStringField(TEXT("sha256"),Hash); Entries.Add(MakeShared<FJsonValueObject>(Entry)); }
 if(Index) { Index->SetStringField(TEXT("schema"),TEXT("URB-project-and-tool-content-v1")); Index->SetArrayField(TEXT("files"),Entries); Index->SetStringField(TEXT("sha256"),SHA256Text(Combined)); }
 return SHA256Text(Combined);
}
static TArray<TSharedPtr<FJsonValue>> URBVector(double X,double Y,double Z) { return {MakeShared<FJsonValueNumber>(X),MakeShared<FJsonValueNumber>(Y),MakeShared<FJsonValueNumber>(Z)}; }
TSharedRef<FJsonObject> FURBMetadata::Invariants(UWorld* World,ACameraActor* Camera) {
 auto Out=MakeShared<FJsonObject>(); auto View=MakeShared<FJsonObject>();
 if(Camera && Camera->GetCameraComponent()) { const FVector P=Camera->GetActorLocation(); const FRotator R=Camera->GetActorRotation(); View->SetArrayField(TEXT("location"),URBVector(P.X,P.Y,P.Z)); View->SetArrayField(TEXT("rotation"),URBVector(R.Pitch,R.Yaw,R.Roll)); View->SetNumberField(TEXT("fov"),Camera->GetCameraComponent()->FieldOfView); }
 Out->SetObjectField(TEXT("camera"),View);
 auto Quality=MakeShared<FJsonObject>();
 for(const TCHAR* Name:{TEXT("sg.ResolutionQuality"),TEXT("sg.ViewDistanceQuality"),TEXT("sg.AntiAliasingQuality"),TEXT("sg.ShadowQuality"),TEXT("sg.GlobalIlluminationQuality"),TEXT("sg.ReflectionQuality"),TEXT("sg.PostProcessQuality"),TEXT("sg.TextureQuality"),TEXT("sg.EffectsQuality"),TEXT("sg.FoliageQuality"),TEXT("sg.ShadingQuality")}) { auto* C=IConsoleManager::Get().FindConsoleVariable(Name); Quality->SetStringField(Name,C?C->GetString():TEXT("Missing")); }
 Out->SetObjectField(TEXT("scalability"),Quality);
 auto CVars=MakeShared<FJsonObject>();
 for(const TCHAR* Name:{TEXT("r.ScreenPercentage"),TEXT("r.VSync"),TEXT("t.MaxFPS"),TEXT("r.DynamicRes.OperationMode"),TEXT("r.GPUCsvStatsEnabled"),TEXT("csv.AlwaysShowFrameCount")}) { auto* C=IConsoleManager::Get().FindConsoleVariable(Name); CVars->SetStringField(Name,C?C->GetString():TEXT("Missing")); }
 Out->SetObjectField(TEXT("environmentCVars"),CVars);
 TArray<FString> Transforms;
 for(TActorIterator<AActor> It(World);It;++It) { const FVector P=It->GetActorLocation(),S=It->GetActorScale3D();const FRotator R=It->GetActorRotation();auto Transform=MakeShared<FJsonObject>();Transform->SetStringField(TEXT("actor"),It->GetName());Transform->SetArrayField(TEXT("location"),URBVector(P.X,P.Y,P.Z));Transform->SetArrayField(TEXT("rotation"),URBVector(R.Pitch,R.Yaw,R.Roll));Transform->SetArrayField(TEXT("scale"),URBVector(S.X,S.Y,S.Z));Transforms.Add(Json(Transform)); }
 Transforms.Sort(); Out->SetStringField(TEXT("sceneTransformSHA256"),SHA256Text(FString::Join(Transforms,TEXT("\n"))));
 return Out;
}
TSharedRef<FJsonObject> FURBMetadata::Fingerprint(UURBTestPreset* Preset,UWorld* World,ACameraActor* Camera,const FString& ContentHash,const TSharedRef<FJsonObject>& Invariant,TSharedPtr<FJsonObject> ActionDescription) {
 auto P=MakeShared<FJsonObject>();
 P->SetStringField(TEXT("engineVersion"),FEngineVersion::Current().ToString()); P->SetStringField(TEXT("gpu"),GRHIAdapterName); P->SetStringField(TEXT("driver"),GRHIAdapterUserDriverVersion); P->SetStringField(TEXT("os"),FPlatformMisc::GetOSVersion()); P->SetStringField(TEXT("cpu"),FPlatformMisc::GetCPUBrand());
 P->SetStringField(TEXT("rhi"),GDynamicRHI?GDynamicRHI->GetName():TEXT("None")); P->SetStringField(TEXT("featureLevel"),GMaxRHIFeatureLevel==ERHIFeatureLevel::SM6?TEXT("SM6"):TEXT("Other"));
 P->SetArrayField(TEXT("resolution"),{MakeShared<FJsonValueNumber>(Preset->Resolution.X),MakeShared<FJsonValueNumber>(Preset->Resolution.Y)});
 P->SetNumberField(TEXT("screenPercentage"),Preset->ScreenPercentage); P->SetNumberField(TEXT("warmupFrames"),Preset->WarmupFrames); P->SetNumberField(TEXT("captureFrames"),Preset->CaptureFrames); P->SetNumberField(TEXT("targetFPSBudgetOnly"),Preset->TargetFPS);
 P->SetStringField(TEXT("sceneType"),Preset->SceneType); P->SetStringField(TEXT("sceneStatePolicy"),Preset->SceneStateDeclaredStatic?TEXT("DeclaredStatic"):TEXT("Unverified"));
 P->SetStringField(TEXT("worldPackage"),World->GetOutermost()->GetName()); P->SetStringField(TEXT("contentSHA256"),ContentHash);
 P->SetObjectField(TEXT("camera"),Invariant->GetObjectField(TEXT("camera"))); P->SetObjectField(TEXT("scalability"),Invariant->GetObjectField(TEXT("scalability"))); P->SetObjectField(TEXT("environmentCVars"),Invariant->GetObjectField(TEXT("environmentCVars"))); P->SetStringField(TEXT("sceneTransformSHA256"),Invariant->GetStringField(TEXT("sceneTransformSHA256")));
 P->SetStringField(TEXT("runnerBuildSHA256"),FileSHA256(FModuleManager::Get().GetModuleFilename(TEXT("URBenchmark"))));
 auto A=MakeShared<FJsonObject>();
 A->SetStringField(TEXT("actionType"),StaticEnum<EURBActionType>()->GetNameStringByValue((int64)Preset->ActionType)); A->SetStringField(TEXT("targetActorTag"),Preset->TargetActorTag.ToString()); A->SetStringField(TEXT("targetComponentTag"),Preset->TargetComponentTag.ToString()); A->SetNumberField(TEXT("materialSlot"),Preset->MaterialSlot);
 A->SetStringField(TEXT("parameterName"),Preset->ScalarParameterName.ToString()); A->SetNumberField(TEXT("valueA"),Preset->ScalarValueA); A->SetStringField(TEXT("materialA"),Preset->VariantA.ToSoftObjectPath().ToString());
 A->SetStringField(TEXT("visibilityScope"),StaticEnum<EURBVisibilityScope>()->GetNameStringByValue((int64)Preset->VisibilityScope)); A->SetBoolField(TEXT("visibleA"),Preset->VisibleA); A->SetBoolField(TEXT("hiddenInGameA"),Preset->HiddenInGameA); A->SetStringField(TEXT("shadowPolicy"),StaticEnum<EURBShadowPolicy>()->GetNameStringByValue((int64)Preset->ShadowPolicy)); A->SetStringField(TEXT("cvarName"),Preset->ConsoleVariableName.ToString()); A->SetNumberField(TEXT("cvarValueA"),Preset->ConsoleValueA);
 if(ActionDescription && ActionDescription->HasTypedField<EJson::Object>(TEXT("original"))) {
  auto Original=ActionDescription->GetObjectField(TEXT("original"));
  if(Preset->ActionType==EURBActionType::ScalarParameter) { A->SetStringField(TEXT("originalMaterial"),Original->GetStringField(TEXT("material"))); A->SetNumberField(TEXT("originalScalar"),Original->GetNumberField(TEXT("scalarValue"))); }
  if(Preset->ActionType==EURBActionType::ActorVisibility) A->SetObjectField(TEXT("originalVisibility"),Original);
 }
 P->SetObjectField(TEXT("actionA"),A);
 auto Out=MakeShared<FJsonObject>();const FString Payload=Json(P); Out->SetNumberField(TEXT("schema_version"),1); Out->SetObjectField(TEXT("payload"),P); Out->SetStringField(TEXT("payloadJson"),Payload); Out->SetStringField(TEXT("sha256"),SHA256Text(Payload)); return Out;
}
