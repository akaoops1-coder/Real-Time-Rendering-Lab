#include "URBRunner.h"
#include "URBAction.h"
#include "URBMetadata.h"
#include "Camera/CameraActor.h"
#include "Components/MeshComponent.h"
#include "Components/InputComponent.h"
#include "Engine/Engine.h"
#include "Engine/GameViewportClient.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/GameUserSettings.h"
#include "Kismet/GameplayStatics.h"
#include "HAL/FileManager.h"
#include "HAL/IConsoleManager.h"
#include "Misc/FileHelper.h"
#include "Misc/Paths.h"
#include "Misc/Parse.h"
#include "Misc/CommandLine.h"
#include "Misc/EngineVersion.h"
#include "Serialization/JsonSerializer.h"
#include "Serialization/JsonWriter.h"
#include "Dom/JsonObject.h"
#include "ProfilingDebugging/CsvProfiler.h"
#include "ShaderCompiler.h"
#include "ShaderPipelineCache.h"
#include "ContentStreaming.h"
#include "RHI.h"
#include "DynamicRHI.h"
#include "UnrealClient.h"
#include "InputCoreTypes.h"

static FString URBStateName(EURBRunState State) { return StaticEnum<EURBRunState>()->GetNameStringByValue((int64)State); }
static bool URBTerminal(EURBRunState S) { return S==EURBRunState::COMPLETED || S==EURBRunState::FAILED || S==EURBRunState::CANCELLED; }

AURBRunner::AURBRunner() { PrimaryActorTick.bCanEverTick=true; Capture=CreateDefaultSubobject<UURBCaptureComponent>(TEXT("CaptureHelper")); }
void AURBRunner::BeginPlay() {
 Super::BeginPlay();
 Capture->OnCaptureFinished.AddDynamic(this,&AURBRunner::CaptureFinished);
 bAutoExit=FParse::Param(FCommandLine::Get(),TEXT("URBAutoExit"));
#if WITH_DEV_AUTOMATION_TESTS
 FParse::Value(FCommandLine::Get(),TEXT("URBValidationScenario="),Scenario);
 if(Scenario==TEXT("ConsoleOriginalLayer")) { if(auto* C=IConsoleManager::Get().FindConsoleVariable(TEXT("r.Tonemapper.Sharpen"))) C->Set(TEXT("0.75"),ECVF_SetByConsole); Log(TEXT("TEST_SETUP original Console source sharpen=0.75")); }
#endif
 FString OverridePath;
 if(FParse::Value(FCommandLine::Get(),TEXT("URBPreset="),OverridePath)) Preset=LoadObject<UURBTestPreset>(nullptr,*OverridePath);
 // Actor BeginPlay can precede a sized standalone viewport and player possession.
 // Snapshot original camera/resolution only after the first valid game frame.
 bPendingAutoStart=AutoRunOnBeginPlay;
}
void AURBRunner::Log(const FString& Message) {
 UE_LOG(LogTemp,Display,TEXT("URB %s"),*Message);
 if(!OutputDirectory.IsEmpty()) FFileHelper::SaveStringToFile(FDateTime::UtcNow().ToIso8601()+TEXT(" ")+Message+TEXT("\n"),*(OutputDirectory/TEXT("Execution.log")),FFileHelper::EEncodingOptions::ForceUTF8WithoutBOM,&IFileManager::Get(),FILEWRITE_Append);
}
void AURBRunner::SetState(EURBRunState NewState,const FString& Message) {
 if(NewState==EURBRunState::CAPTURING && !bScreenMessagesBackedUp) { bOriginalScreenMessages=GAreScreenMessagesEnabled; bScreenMessagesBackedUp=true; GAreScreenMessagesEnabled=false; }
 else if(NewState!=EURBRunState::CAPTURING && bScreenMessagesBackedUp) { GAreScreenMessagesEnabled=bOriginalScreenMessages; bScreenMessagesBackedUp=false; }
 State=NewState; LastMessage=Message; StageStart=FPlatformTime::Seconds(); FrameCounter=0;
 Log(URBStateName(State)+TEXT(" ")+Message); SaveManifest();
 if(GEngine) {
  const uint64 Key=(uint64)(UPTRINT)this;
  GEngine->RemoveOnScreenDebugMessage(Key);
  if(State!=EURBRunState::CAPTURING) GEngine->AddOnScreenDebugMessage(Key,URBTerminal(State)?60.f:600.f,State==EURBRunState::FAILED?FColor::Red:FColor::Cyan,TEXT("URB ")+URBStateName(State)+TEXT(" — ")+Message);
 }
}
bool AURBRunner::Resolve(FString& Error) {
 if(!Active) { Error=TEXT("Preset is missing"); return false; }
 if(Active->TestID.IsNone() || Active->CameraTag.IsNone()) { Error=TEXT("TestID and identification Tags must be set"); return false; }
 if(Active->WarmupFrames<1 || Active->CaptureFrames<1 || Active->RepeatCount<1 || Active->RepeatCount>50 || Active->Resolution.X<64 || Active->Resolution.Y<64 || Active->TargetFPS<1 || !FMath::IsFinite(Active->ScreenPercentage) || Active->ScreenPercentage<10 || Active->ScreenPercentage>200) { Error=TEXT("Invalid capture configuration"); return false; }
 Action=NewObject<UURBAction>(this);
 if(!Action->Resolve(Active,GetWorld(),Error)) return false;
 TArray<AActor*> Actors;
 Actors.Reset(); UGameplayStatics::GetAllActorsWithTag(GetWorld(),Active->CameraTag,Actors);
 if(Actors.Num()!=1 || !(Camera=Cast<ACameraActor>(Actors.Num()==1?Actors[0]:nullptr))) { Error=FString::Printf(TEXT("CameraTag '%s' matched %d actors; one CameraActor required"),*Active->CameraTag.ToString(),Actors.Num()); return false; }
 return true;
}
void AURBRunner::ValidatePreset() {
 if(State!=EURBRunState::IDLE && !URBTerminal(State)) { UE_LOG(LogTemp,Warning,TEXT("URB Validate Preset is unavailable during an active run")); return; }
 Active=Preset; FString Error; const bool bValid=Resolve(Error);
 LastMessage=bValid?TEXT("VALID: Action configuration, unique targets and Camera resolved"):Error;
 UE_LOG(LogTemp,Display,TEXT("URB VALIDATE %s"),*LastMessage);
 if(GEngine) GEngine->AddOnScreenDebugMessage((uint64)(UPTRINT)this,15.f,bValid?FColor::Green:FColor::Red,LastMessage);
}
void AURBRunner::StartBenchmark() {
 if(State!=EURBRunState::IDLE && !URBTerminal(State)) return;
 if(!GetWorld() || (GetWorld()->WorldType!=EWorldType::Game && GetWorld()->WorldType!=EWorldType::PIE)) { LastMessage=TEXT("Use Unreal Play > Standalone Game to run"); return; }
 if(!GetWorld()->HasBegunPlay() || !GEngine || !GEngine->GameViewport || !GEngine->GameViewport->Viewport || GEngine->GameViewport->Viewport->GetSizeXY().X<1 || GEngine->GameViewport->Viewport->GetSizeXY().Y<1) { bPendingAutoStart=true; LastMessage=TEXT("Waiting for initialized game viewport"); return; }
 Records.Reset(); Sequence.Reset(); SavedCVars.Reset(); ContentSnapshotHash.Reset(); InvariantSnapshotJSON.Reset(); CaptureIndex=0; PrepareStage=0; bOriginalSaved=false; bCancelPending=false; bFaultUsed=false; bRestorationApplied=false; bActionRestored=true; Action=nullptr;
 Active=Preset?DuplicateObject<UURBTestPreset>(Preset,this):nullptr;
 const FString ID=Active?FPaths::MakeValidFileName(Active->TestID.ToString()):TEXT("InvalidPreset");
 RunID=FDateTime::UtcNow().ToString(TEXT("%Y%m%dT%H%M%S"))+TEXT("_")+ID+TEXT("_")+FGuid::NewGuid().ToString(EGuidFormats::Digits).Left(8);
 OutputDirectory=FPaths::ConvertRelativePathToFull(FPaths::ProjectSavedDir()/TEXT("URBenchmark")/RunID);
 if(!IFileManager::Get().MakeDirectory(*(OutputDirectory/TEXT("Raw")),true)) { State=EURBRunState::FAILED; LastMessage=TEXT("Cannot create output directory"); FinishedAt=FPlatformTime::Seconds(); return; }
 Manifest=MakeShared<FJsonObject>();
 Manifest->SetNumberField(TEXT("schemaVersion"),3); Manifest->SetBoolField(TEXT("sourceSnapshotStable"),false);
 Manifest->SetStringField(TEXT("runID"),RunID); Manifest->SetStringField(TEXT("testID"),ID);
 Manifest->SetStringField(TEXT("preset"),Preset?Preset->GetPathName():TEXT("Missing"));
 if(Active) Manifest->SetStringField(TEXT("actionType"),StaticEnum<EURBActionType>()->GetNameStringByValue((int64)Active->ActionType));
 Manifest->SetStringField(TEXT("engineVersion"),FEngineVersion::Current().ToString());
 Manifest->SetStringField(TEXT("gpu"),GRHIAdapterName); Manifest->SetStringField(TEXT("rhi"),GDynamicRHI?GDynamicRHI->GetName():TEXT("None"));
 Manifest->SetStringField(TEXT("featureLevel"),GMaxRHIFeatureLevel==ERHIFeatureLevel::SM6?TEXT("SM6"):TEXT("Other"));
 Manifest->SetStringField(TEXT("scope"),TEXT("Phase3 provenance for external Analyzer; unchanged action and CSV capture core"));
 Manifest->SetStringField(TEXT("validationScenario"),Scenario); Manifest->SetBoolField(TEXT("autoExit"),bAutoExit);
 Manifest->SetStringField(TEXT("startedUTC"),FDateTime::UtcNow().ToIso8601());
 SetState(EURBRunState::VALIDATING,TEXT("Checking Preset, Action support, unique targets and Camera"));
 FString Error;
 if(!Resolve(Error)) { BeginRestore(EURBRunState::FAILED,Error); return; }
 if(FCsvProfiler::IsCapturing() || FCsvProfiler::Get()->IsWritingFile() || FCsvProfiler::Get()->IsEndCapturePending()) { BeginRestore(EURBRunState::FAILED,TEXT("CSV Profiler already busy; external capture left untouched")); return; }
 Manifest->SetStringField(TEXT("testName"),Active->TestName); Manifest->SetStringField(TEXT("target"),Action->GetTargetPath());
 Manifest->SetStringField(TEXT("actionType"),StaticEnum<EURBActionType>()->GetNameStringByValue((int64)Active->ActionType));
 Manifest->SetStringField(TEXT("camera"),Camera->GetPathName()); Manifest->SetStringField(TEXT("calibrationReferenceRunID"),Active->CalibrationReferenceRunID);
 Manifest->SetNumberField(TEXT("warmupFrames"),Active->WarmupFrames); Manifest->SetNumberField(TEXT("captureFrames"),Active->CaptureFrames);
 Manifest->SetNumberField(TEXT("repeatCount"),Active->RepeatCount); Manifest->SetNumberField(TEXT("targetFPSBudgetOnly"),Active->TargetFPS);
 Manifest->SetNumberField(TEXT("screenPercentageRequested"),Active->ScreenPercentage);
 Manifest->SetStringField(TEXT("sceneType"),Active->SceneType);
 Manifest->SetStringField(TEXT("runMode"),StaticEnum<EURBRunMode>()->GetNameStringByValue((int64)Active->RunMode)); Manifest->SetBoolField(TEXT("runCalibration"),Active->RunCalibration);
 auto AppendOrder=[this]() { for(int32 I=0;I<Active->RepeatCount;I++) { Sequence.Add(I%2!=0); Sequence.Add(I%2==0); } };
 if(Active->RunMode==EURBRunMode::CalibrationValidation || Active->RunCalibration) AppendOrder();
 if(Active->RunMode==EURBRunMode::StandardBenchmark) AppendOrder();
 Manifest->SetNumberField(TEXT("expectedCaptures"),Sequence.Num());
 SetupEnvironment();
}
bool AURBRunner::SetTemporaryCVar(const TCHAR* Name,const FString& Value) {
 FURBCVarOverride Backup; FString Error; const bool Applied=Backup.Begin(Name,Value,Error);
 if(Backup.bSnapshot) SavedCVars.Add(Backup);
 if(!Applied) { BeginRestore(EURBRunState::FAILED,TEXT("Environment CVar failed: ")+Error); return false; }
 Log(FString::Printf(TEXT("CVAR_APPLY %s=%s"),Name,*Value)); return true;
}
void AURBRunner::SetupEnvironment() {
 auto* PC=GetWorld()->GetFirstPlayerController();
 if(!PC || !GEngine || !GEngine->GameViewport || !GEngine->GameViewport->Viewport) { BeginRestore(EURBRunState::FAILED,TEXT("PlayerController or viewport missing")); return; }
 FString Error; if(!Action->SnapshotAndPrepare(Error)) { BeginRestore(EURBRunState::FAILED,Error); return; }
 auto ActionDescription=MakeShared<FJsonObject>(); Action->Describe(ActionDescription); Manifest->SetObjectField(TEXT("action"),ActionDescription);
 auto ContentIndex=MakeShared<FJsonObject>(); ContentSnapshotHash=FURBMetadata::ContentSHA256(ContentIndex);
 FFileHelper::SaveStringToFile(FURBMetadata::Json(ContentIndex),*(OutputDirectory/TEXT("SourceContentIndex.json")),FFileHelper::EEncodingOptions::ForceUTF8WithoutBOM);
 Manifest->SetStringField(TEXT("sourceContentSHA256"),ContentSnapshotHash);
 OriginalViewTarget=PC->GetViewTarget();
 OriginalResolution=GEngine->GameViewport->Viewport->GetSizeXY(); OriginalWindowMode=(int32)GEngine->GameViewport->Viewport->GetWindowMode();
 bOriginalSaved=true;
 PC->SetViewTarget(Camera); EnableInput(PC); if(InputComponent) InputComponent->BindKey(EKeys::Escape,IE_Pressed,this,&AURBRunner::CancelBenchmark);
 if(!SetTemporaryCVar(TEXT("r.ScreenPercentage"),FString::SanitizeFloat(Active->ScreenPercentage)) ||
    !SetTemporaryCVar(TEXT("r.VSync"),TEXT("0")) || !SetTemporaryCVar(TEXT("t.MaxFPS"),TEXT("0")) ||
    !SetTemporaryCVar(TEXT("r.DynamicRes.OperationMode"),TEXT("0")) || !SetTemporaryCVar(TEXT("r.GPUCsvStatsEnabled"),TEXT("1")) ||
    !SetTemporaryCVar(TEXT("csv.AlwaysShowFrameCount"),TEXT("0"))) return;
 UGameUserSettings::RequestResolutionChange(Active->Resolution.X,Active->Resolution.Y,(EWindowMode::Type)OriginalWindowMode,false);
 if(!ApplyAction(false,Error)) { BeginRestore(EURBRunState::FAILED,Error); return; }
 SetState(EURBRunState::PREPARING,TEXT("Preparing A/B shaders and resources before measurement"));
 Action->PrepareResources();
 if(FParse::Param(FCommandLine::Get(),TEXT("URBScreenshot"))) FScreenshotRequest::RequestScreenshot(OutputDirectory/TEXT("Standalone_PreCapture.png"),false,false);
}
bool AURBRunner::Ready() const {
 return !IsAsyncLoading() && (!GShaderCompilingManager || !GShaderCompilingManager->IsCompiling())
  && Action && Action->Ready()
  && IStreamingManager::Get().GetNumWantingResources()==0 && FShaderPipelineCache::NumPrecompilesRemaining()==0;
}
bool AURBRunner::IsCalibrationCapture() const { return Active && (Active->RunMode==EURBRunMode::CalibrationValidation || (Active->RunCalibration && CaptureIndex<Active->RepeatCount*2)); }
bool AURBRunner::CheckInvariants() const { return !InvariantSnapshotJSON.IsEmpty() && FURBMetadata::Json(FURBMetadata::Invariants(GetWorld(),Camera))==InvariantSnapshotJSON; }
bool AURBRunner::ApplyAction(bool bB,FString& Error) {
 if(!Action || !Action->Apply(bB,Error)) return false;
#if WITH_DEV_AUTOMATION_TESTS
 if((Scenario==TEXT("ActionApplyFailure") || Scenario==TEXT("MaterialApplyFailure")) && PrepareStage>=2 && !bFaultUsed) {
  bFaultUsed=true; FString FaultError; Action->Apply(!bB,FaultError); Log(TEXT("TEST_FAULT injected opposing Action state before readback"));
 }
#endif
 auto Readback=MakeShared<FJsonObject>(); const bool Verified=Action->Verify(bB,Readback,Error);
 FString Json; FJsonSerializer::Serialize(Readback,TJsonWriterFactory<>::Create(&Json));
 Log(TEXT("ACTION_READBACK ")+Json); return Verified;
}
void AURBRunner::BeginNextCapture() {
 if(CaptureIndex>=Sequence.Num()) { BeginRestore(EURBRunState::COMPLETED,TEXT("All requested captures validated")); return; }
 FString Error; const bool ActualB=Sequence[CaptureIndex] && !IsCalibrationCapture();
 if(!ApplyAction(ActualB,Error)) { BeginRestore(EURBRunState::FAILED,Error); return; }
 // All provenance file I/O finishes before this capture's 120 ready warmup frames.
 if(InvariantSnapshotJSON.IsEmpty()) {
  const auto Invariant=FURBMetadata::Invariants(GetWorld(),Camera); InvariantSnapshotJSON=FURBMetadata::Json(Invariant);
  Manifest->SetObjectField(TEXT("measurementFingerprint"),FURBMetadata::Fingerprint(Active,GetWorld(),Camera,ContentSnapshotHash,Invariant,Manifest->GetObjectField(TEXT("action"))));
 }
 SetState(EURBRunState::WARMUP,FString::Printf(TEXT("%s Variant %s / Capture %d of %d"),IsCalibrationCapture()?TEXT("Calibration"):TEXT("Benchmark"),Sequence[CaptureIndex]?TEXT("B"):TEXT("A"),CaptureIndex+1,Sequence.Num()));
}
void AURBRunner::Tick(float DeltaSeconds) {
 Super::Tick(DeltaSeconds);
 if(bPendingAutoStart && State==EURBRunState::IDLE && GetWorld()->HasBegunPlay() && GetWorld()->GetFirstPlayerController()) { StartBenchmark(); if(State!=EURBRunState::IDLE) bPendingAutoStart=false; return; }
 if(URBTerminal(State)) { if(bAutoExit && FPlatformTime::Seconds()-FinishedAt>2) FPlatformMisc::RequestExit(false); return; }
 if(State==EURBRunState::RESTORING) { FinishRestore(); return; }
 if(State==EURBRunState::PREPARING || State==EURBRunState::WARMUP) {
  if(FPlatformTime::Seconds()-StageStart>600) { BeginRestore(EURBRunState::FAILED,TEXT("Shader/resource preparation timed out")); return; }
  if(!Ready()) {
   if(FPlatformTime::Seconds()-LastPrepareLog>5) { LastPrepareLog=FPlatformTime::Seconds(); Log(FString::Printf(TEXT("PREPARATION_WAIT async=%d shaders=%d actionReady=%d streaming=%d pso=%d"),IsAsyncLoading(),GShaderCompilingManager?GShaderCompilingManager->IsCompiling():false,Action?Action->Ready():false,IStreamingManager::Get().GetNumWantingResources(),FShaderPipelineCache::NumPrecompilesRemaining())); }
   FrameCounter=0; return;
  }
  if(GEngine->GameViewport->Viewport->GetSizeXY()!=Active->Resolution) { if(FPlatformTime::Seconds()-StageStart>10) BeginRestore(EURBRunState::FAILED,TEXT("Requested resolution was not applied")); return; }
  ++FrameCounter;
#if WITH_DEV_AUTOMATION_TESTS
  if(State==EURBRunState::WARMUP && Scenario==TEXT("CancelWarmup") && FrameCounter==30) { Log(TEXT("TEST_FAULT scheduled user cancel during Warmup")); CancelBenchmark(); return; }
  if(State==EURBRunState::WARMUP && Scenario==TEXT("CaptureBusy") && FrameCounter==1 && !bFaultUsed) { bFaultUsed=true; Log(TEXT("TEST_FAULT occupying CSV profiler before helper capture")); FCsvProfiler::Get()->BeginCapture(1000,OutputDirectory/TEXT("Raw"),TEXT("Fault_ExternalCapture.csv")); }
#endif
  if(FrameCounter<Active->WarmupFrames) return;
  if(State==EURBRunState::PREPARING) {
   FrameCounter=0;
   if(PrepareStage++==0) { FString Error; if(!ApplyAction(true,Error)) BeginRestore(EURBRunState::FAILED,Error); }
   else { PrepareStage=2; BeginNextCapture(); } return;
  }
  const bool ActualB=Sequence[CaptureIndex] && !IsCalibrationCapture();
  const bool InvariantsBefore=CheckInvariants();
  if(Active->SceneStateDeclaredStatic && !InvariantsBefore) { BeginRestore(EURBRunState::FAILED,TEXT("Declared static scene, Camera or Scalability changed before Capture")); return; }
  auto Readback=MakeShared<FJsonObject>(); FString VerifyError;
  if(!Action || !Action->Verify(ActualB,Readback,VerifyError)) { BeginRestore(EURBRunState::FAILED,TEXT("Action changed during Warmup: ")+VerifyError); return; }
  TArray<TSharedPtr<FJsonValue>> EnvironmentReadbacks;
  for(const auto& Saved:SavedCVars) {
   auto Check=MakeShared<FJsonObject>();
   if(!Saved.Verify(Saved.AppliedValue,Check,VerifyError)) { BeginRestore(EURBRunState::FAILED,TEXT("Environment changed during Warmup: ")+VerifyError); return; }
   EnvironmentReadbacks.Add(MakeShared<FJsonValueObject>(Check));
  }
  if(GetWorld()->GetFirstPlayerController()->GetViewTarget()!=Camera) { BeginRestore(EURBRunState::FAILED,TEXT("Camera view target changed during Warmup")); return; }
  const FString Label=Sequence[CaptureIndex]?TEXT("B"):TEXT("A");
  auto Record=MakeShared<FJsonObject>(); Record->SetNumberField(TEXT("captureIndex"),CaptureIndex); Record->SetStringField(TEXT("variant"),Label);
  Record->SetStringField(TEXT("mode"),IsCalibrationCapture()?TEXT("Calibration"):TEXT("Benchmark"));
  Record->SetStringField(TEXT("actualMaterial"),Action->GetActualMaterialPath());
  Record->SetStringField(TEXT("actionType"),StaticEnum<EURBActionType>()->GetNameStringByValue((int64)Active->ActionType));
  Record->SetStringField(TEXT("actualActionVariant"),ActualB?TEXT("B"):TEXT("A"));
  Record->SetObjectField(TEXT("actionReadbackBeforeCapture"),Readback);
  Record->SetBoolField(TEXT("invariantEnvironmentVerifiedBefore"),InvariantsBefore); Record->SetStringField(TEXT("captureStartedUTC"),FDateTime::UtcNow().ToIso8601());
  Record->SetStringField(TEXT("measurementFingerprintSHA256"),Manifest->GetObjectField(TEXT("measurementFingerprint"))->GetStringField(TEXT("sha256")));
  Record->SetArrayField(TEXT("environmentReadbackBeforeCapture"),EnvironmentReadbacks);
  Record->SetNumberField(TEXT("captureFramesRequested"),Active->CaptureFrames); Record->SetNumberField(TEXT("warmupFramesActual"),FrameCounter);
  Record->SetStringField(TEXT("status"),TEXT("REQUESTED")); Records.Add(MakeShared<FJsonValueObject>(Record));
  const FString Filename=FString::Printf(TEXT("%s_%03d_%s.csv"),IsCalibrationCapture()?TEXT("AA"):TEXT("AB"),CaptureIndex,*Label);
  Record->SetStringField(TEXT("file"),Filename);
  Record->SetBoolField(TEXT("screenMessagesDisabledForCapture"),true);
  TMap<FString,FString> Metadata={{TEXT("URBTestID"),Active->TestID.ToString()},{TEXT("URBRunID"),RunID},{TEXT("URBCaptureIndex"),FString::FromInt(CaptureIndex)},{TEXT("URBVariant"),Label},{TEXT("URBActualMaterial"),Action->GetActualMaterialPath()},{TEXT("URBMode"),IsCalibrationCapture()?TEXT("Calibration"):TEXT("Benchmark")},{TEXT("URBCaptureFrames"),FString::FromInt(Active->CaptureFrames)},{TEXT("URBActionType"),StaticEnum<EURBActionType>()->GetNameStringByValue((int64)Active->ActionType)},{TEXT("URBActualActionVariant"),ActualB?TEXT("B"):TEXT("A")}};
  Metadata.Add(TEXT("URBMeasurementFingerprint"),Record->GetStringField(TEXT("measurementFingerprintSHA256"))); Metadata.Add(TEXT("URBSourceSchemaVersion"),TEXT("3"));
  Manifest->SetStringField(TEXT("actualResolution"),FString::Printf(TEXT("%dx%d"),Active->Resolution.X,Active->Resolution.Y));
  SetState(EURBRunState::CAPTURING,FString::Printf(TEXT("Variant %s / Capture %d of %d"),*Label,CaptureIndex+1,Sequence.Num()));
  if(!Capture->StartCapture(Active->CaptureFrames,OutputDirectory/TEXT("Raw"),Filename,Metadata)) {
#if WITH_DEV_AUTOMATION_TESTS
   if(Scenario==TEXT("CaptureBusy") && bFaultUsed) FCsvProfiler::Get()->EndCapture();
#endif
   Record->SetStringField(TEXT("status"),TEXT("FAILED")); Record->SetStringField(TEXT("error"),Capture->LastError); BeginRestore(EURBRunState::FAILED,Capture->LastError);
  }
 } else if(State==EURBRunState::CAPTURING) {
  ++FrameCounter;
#if WITH_DEV_AUTOMATION_TESTS
  if(Scenario==TEXT("ActionChangedDuringCapture") && FrameCounter==30 && !bFaultUsed) { bFaultUsed=true; FString FaultError; Action->Apply(!(Sequence[CaptureIndex] && !IsCalibrationCapture()),FaultError); Log(TEXT("TEST_FAULT opposing Action state during Capture")); }
  if(Scenario==TEXT("CancelCapture") && FrameCounter==30 && !bCancelPending) { Log(TEXT("TEST_FAULT scheduled user cancel during Capture")); CancelBenchmark(); }
#endif
 }
}
void AURBRunner::CaptureFinished(bool bSuccess,const FString& Filename,const FString& Error) {
 if(bEnding || State!=EURBRunState::CAPTURING) return;
 if(Records.Num() && !Filename.IsEmpty()) Records.Last()->AsObject()->SetStringField(TEXT("sha256"),FURBMetadata::FileSHA256(Filename));
 auto Readback=MakeShared<FJsonObject>(); FString VerifyError;
 const bool bActionStillValid=Action && Action->Verify(Sequence[CaptureIndex] && !IsCalibrationCapture(),Readback,VerifyError);
 FString FinalError=bActionStillValid?Error:TEXT("Action changed during Capture: ")+VerifyError;
 bool bEnvironmentStillValid=GetWorld()->GetFirstPlayerController() && GetWorld()->GetFirstPlayerController()->GetViewTarget()==Camera && GEngine && GEngine->GameViewport && GEngine->GameViewport->Viewport && GEngine->GameViewport->Viewport->GetSizeXY()==Active->Resolution;
 TArray<TSharedPtr<FJsonValue>> EnvironmentReadbacks;
 for(const auto& Saved:SavedCVars) { auto Check=MakeShared<FJsonObject>(); FString EnvironmentError; bEnvironmentStillValid &= Saved.Verify(Saved.AppliedValue,Check,EnvironmentError); EnvironmentReadbacks.Add(MakeShared<FJsonValueObject>(Check)); }
 if(!bEnvironmentStillValid) FinalError+=TEXT("; Camera, resolution or environment CVar changed during Capture");
 const bool InvariantsAfter=CheckInvariants();
 if(Records.Num()) { auto R=Records.Last()->AsObject(); R->SetBoolField(TEXT("invariantEnvironmentVerifiedAfter"),InvariantsAfter); R->SetStringField(TEXT("captureCompletedUTC"),FDateTime::UtcNow().ToIso8601()); }
 if(Active->SceneStateDeclaredStatic && !InvariantsAfter) { bEnvironmentStillValid=false; FinalError+=TEXT("; Declared static scene, Camera or Scalability changed during Capture"); }
 bSuccess &= bActionStillValid && bEnvironmentStillValid;
 if(Records.Num()) { auto R=Records.Last()->AsObject(); R->SetStringField(TEXT("file"),FPaths::GetCleanFilename(Filename)); R->SetStringField(TEXT("status"),bCancelPending?TEXT("CANCELLED"):bSuccess?TEXT("PASS"):TEXT("FAILED")); R->SetNumberField(TEXT("validFrames"),Capture->ValidFrameCount); R->SetStringField(TEXT("error"),FinalError); R->SetObjectField(TEXT("actionReadbackAfterCapture"),Readback); R->SetBoolField(TEXT("actionStateVerifiedAfterCapture"),bActionStillValid); R->SetArrayField(TEXT("environmentReadbackAfterCapture"),EnvironmentReadbacks); R->SetBoolField(TEXT("environmentStateVerifiedAfterCapture"),bEnvironmentStillValid); }
 Log(FString::Printf(TEXT("CAPTURE_FINISHED index=%d success=%s frames=%d file=%s error=%s"),CaptureIndex,bSuccess?TEXT("true"):TEXT("false"),Capture->ValidFrameCount,*Filename,*Error));
 if(bCancelPending) { BeginRestore(EURBRunState::CANCELLED,TEXT("User cancelled; CSV write completed before restoration")); return; }
 if(!bSuccess) { BeginRestore(EURBRunState::FAILED,FinalError); return; }
 ++CaptureIndex; BeginNextCapture();
}
void AURBRunner::CancelBenchmark() {
 if(State==EURBRunState::IDLE || State==EURBRunState::RESTORING || URBTerminal(State)) return;
 bCancelPending=true; Log(TEXT("CANCEL_REQUESTED"));
 if(Capture->IsBusy()) Capture->CancelCapture(); else BeginRestore(EURBRunState::CANCELLED,TEXT("User cancelled before capture"));
}
void AURBRunner::BeginRestore(EURBRunState Result,const FString& Reason) {
 if(Manifest) Manifest->SetStringField(TEXT("measurementStatus"),Reason.StartsWith(TEXT("UNSUPPORTED"))?TEXT("UNSUPPORTED"):Result==EURBRunState::COMPLETED?TEXT("PASS"):Result==EURBRunState::CANCELLED?TEXT("CANCELLED"):TEXT("FAIL"));
 FinalState=Result; FinishReason=Reason; bRestorationApplied=false; SetState(EURBRunState::RESTORING,Reason); FinishRestore();
}
void AURBRunner::FinishRestore() {
 if(!bRestorationApplied) {
  bRestorationApplied=true;
  if(Manifest && !ContentSnapshotHash.IsEmpty()) { const FString EndHash=FURBMetadata::ContentSHA256(nullptr); Manifest->SetBoolField(TEXT("sourceSnapshotStable"),EndHash==ContentSnapshotHash); Manifest->SetStringField(TEXT("sourceContentSHA256After"),EndHash); }
  auto ActionRestoration=MakeShared<FJsonObject>(); FString ActionRestoreError;
  bActionRestored=!Action || Action->Restore(ActionRestoration,ActionRestoreError);
  if(Manifest) Manifest->SetObjectField(TEXT("actionRestoration"),ActionRestoration);
  if(!bActionRestored) { FinishReason+=TEXT("; ")+ActionRestoreError; Log(TEXT("ACTION_RESTORE_FAILED ")+ActionRestoreError); }
  if(bOriginalSaved) {
   if(auto* PC=GetWorld()->GetFirstPlayerController()) { if(IsValid(OriginalViewTarget)) PC->SetViewTarget(OriginalViewTarget); DisableInput(PC); }
   TArray<TSharedPtr<FJsonValue>> EnvironmentRestorations;
   for(auto& Saved:SavedCVars) { auto Check=MakeShared<FJsonObject>(); FString Error; Saved.Restore(Check,Error); EnvironmentRestorations.Add(MakeShared<FJsonValueObject>(Check)); }
   if(Manifest) Manifest->SetArrayField(TEXT("environmentRestoration"),EnvironmentRestorations);
   UGameUserSettings::RequestResolutionChange(OriginalResolution.X,OriginalResolution.Y,(EWindowMode::Type)OriginalWindowMode,false);
  }
 }
 bool bMaterial=bActionRestored;
 bool bCamera=!bOriginalSaved || (GetWorld()->GetFirstPlayerController() && GetWorld()->GetFirstPlayerController()->GetViewTarget()==OriginalViewTarget);
 bool bCVars=true; for(const auto& Saved:SavedCVars) bCVars &= Saved.IsRestored();
 bool bResolution=!bOriginalSaved || (GEngine && GEngine->GameViewport && GEngine->GameViewport->Viewport && GEngine->GameViewport->Viewport->GetSizeXY()==OriginalResolution && (int32)GEngine->GameViewport->Viewport->GetWindowMode()==OriginalWindowMode);
 if(!bResolution && !bEnding && FPlatformTime::Seconds()-StageStart<5) return;
 if(Manifest) { auto Restoration=MakeShared<FJsonObject>(); Restoration->SetBoolField(TEXT("action"),bActionRestored); Restoration->SetBoolField(TEXT("camera"),bCamera); Restoration->SetBoolField(TEXT("cvarsAndPriorities"),bCVars); Restoration->SetBoolField(TEXT("resolution"),bResolution); Restoration->SetBoolField(TEXT("runtimeChangesMade"),bOriginalSaved); Manifest->SetObjectField(TEXT("restoration"),Restoration); }
 if(!(bMaterial && bCamera && bCVars && bResolution)) { FinalState=EURBRunState::FAILED; if(Manifest) Manifest->SetStringField(TEXT("measurementStatus"),TEXT("FAIL")); FinishReason+=TEXT("; restoration readback failed"); }
 FinishedAt=FPlatformTime::Seconds(); SetState(FinalState,FinishReason);
 if(Manifest) { Manifest->SetStringField(TEXT("finishedUTC"),FDateTime::UtcNow().ToIso8601()); SaveManifest(); }
}
void AURBRunner::SaveManifest() {
 if(!Manifest || OutputDirectory.IsEmpty()) return;
 Manifest->SetStringField(TEXT("status"),URBStateName(State)); Manifest->SetStringField(TEXT("message"),LastMessage);
 Manifest->SetArrayField(TEXT("captures"),Records);
 FString Json; const auto Writer=TJsonWriterFactory<>::Create(&Json); FJsonSerializer::Serialize(Manifest.ToSharedRef(),Writer);
 FFileHelper::SaveStringToFile(Json,*(OutputDirectory/TEXT("Manifest.json")),FFileHelper::EEncodingOptions::ForceUTF8WithoutBOM);
 if(URBTerminal(State)) FFileHelper::SaveStringToFile(Json,*(OutputDirectory/TEXT("Completion.json")),FFileHelper::EEncodingOptions::ForceUTF8WithoutBOM);
}
void AURBRunner::EndPlay(const EEndPlayReason::Type Reason) {
 bEnding=true;
 if(State!=EURBRunState::IDLE && !URBTerminal(State)) {
  if(Records.Num() && Records.Last()->AsObject()->GetStringField(TEXT("status"))==TEXT("REQUESTED")) { Records.Last()->AsObject()->SetStringField(TEXT("status"),TEXT("INTERRUPTED")); Records.Last()->AsObject()->SetStringField(TEXT("error"),TEXT("EndPlay before completed file validation")); }
  if(Capture->IsBusy()) Capture->CancelCapture(); BeginRestore(EURBRunState::CANCELLED,TEXT("EndPlay: best-effort restoration; interrupted capture not a completed benchmark"));
 }
 Capture->OnCaptureFinished.RemoveDynamic(this,&AURBRunner::CaptureFinished);
 if(GEngine) GEngine->RemoveOnScreenDebugMessage((uint64)(UPTRINT)this);
 Super::EndPlay(Reason);
}
