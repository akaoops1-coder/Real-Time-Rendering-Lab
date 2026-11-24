#include "URBAction.h"
#include "Components/MeshComponent.h"
#include "Components/PrimitiveComponent.h"
#include "Components/SceneComponent.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "Materials/MaterialParameters.h"
#include "Kismet/GameplayStatics.h"
#include "HAL/IConsoleManager.h"
#include "Dom/JsonObject.h"

static bool URBScalarValue(UMaterialInterface* Material,FName Name,float& Value) {
 return Material && Material->GetScalarParameterValue(FMaterialParameterInfo(Name),Value) && FMath::IsFinite(Value);
}
static bool URBSameScalar(float A,float B) { return FMath::IsFinite(A) && FMath::IsFinite(B) && FMath::IsNearlyEqual(A,B,FMath::Max(1.e-5f,FMath::Abs(B)*1.e-6f)); }
static FString URBActionName(EURBActionType Type) { return StaticEnum<EURBActionType>()->GetNameStringByValue((int64)Type); }

bool UURBAction::Resolve(UURBTestPreset* InPreset,UWorld* World,FString& Error) {
 Preset=InPreset; Actor=nullptr; Component=nullptr; Mesh=nullptr;
 MaterialA=nullptr; MaterialB=nullptr; OriginalMaterial=nullptr;
 if(!Preset || !World) { Error=TEXT("Preset or World is missing"); return false; }
 if((uint8)Preset->ActionType>(uint8)EURBActionType::ConsoleVariable) { Error=TEXT("UNSUPPORTED: unknown ActionType"); return false; }
 if(Preset->ActionType==EURBActionType::ConsoleVariable) {
  const FString Name=Preset->ConsoleVariableName.ToString();
  const bool bSharpen=Name==TEXT("r.Tonemapper.Sharpen"),bBloom=Name==TEXT("r.BloomQuality");
  if(!bSharpen && !bBloom) { Error=TEXT("UNSUPPORTED: CVar is outside the runtime Allowlist (r.Tonemapper.Sharpen, r.BloomQuality)"); return false; }
  auto* C=IConsoleManager::Get().FindConsoleVariable(*Name);
  if(!C || C->TestFlags((EConsoleVariableFlags)(ECVF_ReadOnly|ECVF_Cheat|ECVF_Unregistered|ECVF_CreatedFromIni)) || !C->TestFlags(ECVF_RenderThreadSafe)) { Error=TEXT("UNSUPPORTED: Allowlisted CVar is absent or its runtime flags are unsupported"); return false; }
  const auto Valid=[bBloom](float V) { return FMath::IsFinite(V) && V>=0 && V<=(bBloom?5.f:10.f) && (!bBloom || V==FMath::FloorToFloat(V)); };
  if(!Valid(Preset->ConsoleValueA) || !Valid(Preset->ConsoleValueB)) { Error=TEXT("UNSUPPORTED: Sharpen requires finite 0..10; BloomQuality requires integer 0..5"); return false; }
  return true;
 }
 if(Preset->TargetActorTag.IsNone()) { Error=TEXT("TargetActorTag must be set for this Action"); return false; }
 TArray<AActor*> Actors; UGameplayStatics::GetAllActorsWithTag(World,Preset->TargetActorTag,Actors);
 if(Actors.Num()!=1) { Error=FString::Printf(TEXT("TargetActorTag '%s' matched %d actors; exactly one required"),*Preset->TargetActorTag.ToString(),Actors.Num()); return false; }
 Actor=Actors[0];
 if(Preset->ActionType==EURBActionType::ActorVisibility && Actor->GetParentActor()) { Error=TEXT("UNSUPPORTED: ChildActor visibility inherits parent render gating; use an independent benchmark Actor"); return false; }
 if(Preset->ActionType==EURBActionType::ActorVisibility && ((uint8)Preset->VisibilityScope>(uint8)EURBVisibilityScope::Component || (uint8)Preset->ShadowPolicy>(uint8)EURBShadowPolicy::DisableHiddenShadows)) { Error=TEXT("UNSUPPORTED: unknown VisibilityScope or ShadowPolicy"); return false; }
 const bool bActorScope=Preset->ActionType==EURBActionType::ActorVisibility && Preset->VisibilityScope==EURBVisibilityScope::Actor;
 if(!bActorScope) {
  if(Preset->TargetComponentTag.IsNone()) { Error=TEXT("TargetComponentTag must be set for this Action"); return false; }
  TArray<USceneComponent*> Components; Actor->GetComponents<USceneComponent>(Components);
  TArray<USceneComponent*> Matches;
  for(auto* C:Components) if(C->ComponentHasTag(Preset->TargetComponentTag) && (Preset->ActionType==EURBActionType::ActorVisibility || C->IsA<UMeshComponent>())) Matches.Add(C);
  if(Matches.Num()!=1) { Error=FString::Printf(TEXT("TargetComponentTag '%s' matched %d eligible components; exactly one required"),*Preset->TargetComponentTag.ToString(),Matches.Num()); return false; }
  Component=Matches[0]; Mesh=Cast<UMeshComponent>(Component);
 }
 if(Preset->ActionType==EURBActionType::ActorVisibility) {
  if(!bActorScope && Preset->ShadowPolicy!=EURBShadowPolicy::PreserveOriginal && !Cast<UPrimitiveComponent>(Component)) { Error=TEXT("UNSUPPORTED: ShadowPolicy requires a PrimitiveComponent"); return false; }
  return true;
 }
 if(!Mesh || Preset->MaterialSlot<0 || Preset->MaterialSlot>=Mesh->GetNumMaterials()) { Error=TEXT("Material Slot is out of range"); return false; }
 OriginalMaterial=Mesh->GetMaterial(Preset->MaterialSlot);
 if(!OriginalMaterial) { Error=TEXT("Original Material Slot is empty"); return false; }
 if(Preset->ActionType==EURBActionType::MaterialSwap) {
  MaterialA=Preset->VariantA.LoadSynchronous(); MaterialB=Preset->VariantB.LoadSynchronous();
  if(!MaterialA || (Preset->RunMode==EURBRunMode::StandardBenchmark && !MaterialB)) { Error=TEXT("Variant Material could not be loaded"); return false; }
  if(!MaterialB) MaterialB=MaterialA;
  return true;
 }
 if(Preset->ScalarParameterName.IsNone() || !FMath::IsFinite(Preset->ScalarValueA) || !FMath::IsFinite(Preset->ScalarValueB)) { Error=TEXT("Scalar Parameter name and finite A/B values are required"); return false; }
 TArray<FMaterialParameterInfo> Infos; TArray<FGuid> IDs; OriginalMaterial->GetAllScalarParameterInfo(Infos,IDs);
 int32 Matches=0;
 for(const auto& Info:Infos) if(Info.Name==Preset->ScalarParameterName && Info.Association==EMaterialParameterAssociation::GlobalParameter) ++Matches;
 if(Matches!=1 || !URBScalarValue(OriginalMaterial,Preset->ScalarParameterName,OriginalScalar)) { Error=TEXT("Scalar Parameter must exist exactly once as a Global scalar on the original Slot Material; layered parameters are unsupported"); return false; }
 FMaterialParameterMetadata Metadata;
 if(!OriginalMaterial->GetParameterValue(EMaterialParameterType::Scalar,FMaterialParameterInfo(Preset->ScalarParameterName),Metadata) || Metadata.PrimitiveDataIndex!=INDEX_NONE) { Error=TEXT("UNSUPPORTED: Custom Primitive Data-backed scalar parameters cannot be controlled by a DMI"); return false; }
 MaterialA=OriginalMaterial; MaterialB=OriginalMaterial;
 return true;
}
bool UURBAction::CheckResolved(FString& Error) const {
 if(!Preset) { Error=TEXT("Action Preset is missing"); return false; }
 if(Preset->ActionType==EURBActionType::ConsoleVariable) return true;
 if(!IsValid(Actor)) { Error=TEXT("Action target Actor became invalid"); return false; }
 if(Preset->ActionType==EURBActionType::ActorVisibility && Preset->VisibilityScope==EURBVisibilityScope::Actor) return true;
 if(!IsValid(Component) || Component->GetOwner()!=Actor) { Error=TEXT("Action target Component became invalid"); return false; }
 if(Preset->ActionType!=EURBActionType::ActorVisibility && (!IsValid(Mesh) || Preset->MaterialSlot<0 || Preset->MaterialSlot>=Mesh->GetNumMaterials())) { Error=TEXT("Action Material Slot became invalid"); return false; }
 return true;
}
bool UURBAction::SnapshotAndPrepare(FString& Error) {
 if(bSnapshot) { Error=TEXT("Action snapshot was already taken"); return false; }
 if(!CheckResolved(Error)) return false;
 Snapshot=MakeShared<FJsonObject>();
 if(Preset->ActionType==EURBActionType::ConsoleVariable) {
  if(!CVar.Snapshot(Preset->ConsoleVariableName.ToString(),Error)) return false;
  bSnapshot=true; CVar.Describe(Snapshot); return true;
 }
 bOriginalActorHidden=Actor->IsHidden();
 Snapshot->SetBoolField(TEXT("actorHiddenInGame"),bOriginalActorHidden);
 if(Preset->ActionType==EURBActionType::ActorVisibility) {
  TArray<USceneComponent*> Components;
  if(Preset->VisibilityScope==EURBVisibilityScope::Actor) Actor->GetComponents<USceneComponent>(Components);
  else Components.Add(Component);
  for(auto* C:Components) {
   FURBVisibilityBackup B; B.Component=C; B.Visible=C->GetVisibleFlag(); B.Hidden=C->bHiddenInGame;
   if(auto* P=Cast<UPrimitiveComponent>(C)) { B.CastShadow=P->CastShadow; B.CastHiddenShadow=P->bCastHiddenShadow; }
   Visibility.Add(B);
  }
  ReadVisibility(Snapshot); bSnapshot=true; return true;
 }
 OriginalMaterial=Mesh->GetMaterial(Preset->MaterialSlot);
 Snapshot->SetStringField(TEXT("material"),GetPathNameSafe(OriginalMaterial));
 if(Preset->ActionType==EURBActionType::ScalarParameter && !URBScalarValue(OriginalMaterial,Preset->ScalarParameterName,OriginalScalar)) { Error=TEXT("Original Scalar Parameter changed before snapshot"); return false; }
 bSnapshot=true;
 if(Preset->ActionType==EURBActionType::ScalarParameter) {
  Snapshot->SetNumberField(TEXT("scalarValue"),OriginalScalar);
  DynamicMaterial=UMaterialInstanceDynamic::Create(OriginalMaterial,this);
  if(!DynamicMaterial) { Error=TEXT("Transient Dynamic Material Instance creation failed"); return false; }
  DynamicMaterial->SetFlags(RF_Transient);
  DynamicMaterial->SetScalarParameterValue(Preset->ScalarParameterName,OriginalScalar);
  MaterialA=DynamicMaterial; MaterialB=DynamicMaterial;
  Mesh->SetMaterial(Preset->MaterialSlot,DynamicMaterial);
  if(Mesh->GetMaterial(Preset->MaterialSlot)!=DynamicMaterial) { Error=TEXT("Dynamic Material Instance attachment readback failed"); return false; }
 }
 return true;
}
bool UURBAction::Apply(bool bB,FString& Error) {
 if(!bSnapshot || !CheckResolved(Error)) { if(Error.IsEmpty()) Error=TEXT("Action has no snapshot"); return false; }
 switch(Preset->ActionType) {
  case EURBActionType::MaterialSwap: Mesh->SetMaterial(Preset->MaterialSlot,bB?MaterialB.Get():MaterialA.Get()); break;
  case EURBActionType::ScalarParameter:
   if(!IsValid(DynamicMaterial)) { Error=TEXT("Reused Dynamic Material Instance became invalid"); return false; }
   DynamicMaterial->SetScalarParameterValue(Preset->ScalarParameterName,bB?Preset->ScalarValueB:Preset->ScalarValueA); break;
  case EURBActionType::ActorVisibility:
   if(Preset->VisibilityScope==EURBVisibilityScope::Actor) Actor->SetActorHiddenInGame(bB?Preset->HiddenInGameB:Preset->HiddenInGameA);
   else { Component->SetVisibility(bB?Preset->VisibleB:Preset->VisibleA,false); Component->SetHiddenInGame(bB?Preset->HiddenInGameB:Preset->HiddenInGameA,false); }
   for(const auto& B:Visibility) if(auto* P=Cast<UPrimitiveComponent>(B.Component)) {
    P->SetCastShadow(Preset->ShadowPolicy==EURBShadowPolicy::DisableShadows?false:B.CastShadow);
    P->SetCastHiddenShadow(Preset->ShadowPolicy==EURBShadowPolicy::DisableHiddenShadows?false:B.CastHiddenShadow);
   }
   break;
  case EURBActionType::ConsoleVariable:
   if(!CVar.Set(FString::SanitizeFloat(bB?Preset->ConsoleValueB:Preset->ConsoleValueA),Error)) return false;
   break;
  default: Error=TEXT("UNSUPPORTED: ActionType"); return false;
 }
 return Verify(bB,nullptr,Error);
}
void UURBAction::ReadVisibility(TSharedPtr<FJsonObject> Out) const {
 if(!Out) return;
 Out->SetBoolField(TEXT("actorHiddenInGame"),IsValid(Actor)?Actor->IsHidden():true);
 TArray<TSharedPtr<FJsonValue>> Values;
 for(const auto& B:Visibility) {
  auto J=MakeShared<FJsonObject>(); auto* C=B.Component.Get();
  J->SetStringField(TEXT("component"),GetPathNameSafe(C)); J->SetBoolField(TEXT("valid"),IsValid(C));
  if(IsValid(C)) {
   J->SetBoolField(TEXT("visibleFlag"),C->GetVisibleFlag()); J->SetBoolField(TEXT("hiddenInGame"),C->bHiddenInGame);
   J->SetBoolField(TEXT("isVisible"),C->IsVisible()); J->SetBoolField(TEXT("shouldRender"),C->ShouldRender()); J->SetBoolField(TEXT("registered"),C->IsRegistered());
   if(auto* P=Cast<UPrimitiveComponent>(C)) { J->SetBoolField(TEXT("castShadow"),P->CastShadow); J->SetBoolField(TEXT("castHiddenShadow"),P->bCastHiddenShadow); }
  }
  Values.Add(MakeShared<FJsonValueObject>(J));
 }
 Out->SetArrayField(TEXT("components"),Values);
}
bool UURBAction::Verify(bool bB,TSharedPtr<FJsonObject> Out,FString& Error) const {
 if(!bSnapshot || !CheckResolved(Error)) { if(Out) Out->SetBoolField(TEXT("verified"),false); return false; }
 bool bOK=true;
 if(Out) { Out->SetStringField(TEXT("actionType"),URBActionName(Preset->ActionType)); Out->SetStringField(TEXT("actualVariant"),bB?TEXT("B"):TEXT("A")); }
 if(Preset->ActionType==EURBActionType::ConsoleVariable) return CVar.Verify(FString::SanitizeFloat(bB?Preset->ConsoleValueB:Preset->ConsoleValueA),Out,Error);
 if(Preset->ActionType==EURBActionType::MaterialSwap) {
  const auto* Expected=bB?MaterialB.Get():MaterialA.Get(); bOK=Mesh->GetMaterial(Preset->MaterialSlot)==Expected;
  if(Out) { Out->SetStringField(TEXT("expectedMaterial"),GetPathNameSafe(Expected)); Out->SetStringField(TEXT("actualMaterial"),GetActualMaterialPath()); }
 } else if(Preset->ActionType==EURBActionType::ScalarParameter) {
  float Actual=0; const float Expected=bB?Preset->ScalarValueB:Preset->ScalarValueA;
  bOK=DynamicMaterial && Mesh->GetMaterial(Preset->MaterialSlot)==DynamicMaterial && URBScalarValue(DynamicMaterial,Preset->ScalarParameterName,Actual) && URBSameScalar(Actual,Expected);
  if(Out) {
   Out->SetStringField(TEXT("parameter"),Preset->ScalarParameterName.ToString()); Out->SetNumberField(TEXT("expectedValue"),Expected); Out->SetNumberField(TEXT("actualValue"),Actual);
   Out->SetStringField(TEXT("dynamicMaterial"),GetPathNameSafe(DynamicMaterial)); Out->SetNumberField(TEXT("dynamicMaterialObjectID"),DynamicMaterial?DynamicMaterial->GetUniqueID():0);
   Out->SetStringField(TEXT("actualMaterial"),GetActualMaterialPath());
  }
 } else if(Preset->ActionType==EURBActionType::ActorVisibility) {
  const bool bActorScope=Preset->VisibilityScope==EURBVisibilityScope::Actor;
  const bool ExpectedActorHidden=bActorScope?(bB?Preset->HiddenInGameB:Preset->HiddenInGameA):bOriginalActorHidden;
  bOK=Actor->IsHidden()==ExpectedActorHidden;
  for(const auto& B:Visibility) {
   auto* C=B.Component.Get(); if(!IsValid(C)) { bOK=false; continue; }
   const bool ExpectedVisible=bActorScope?B.Visible:(bB?Preset->VisibleB:Preset->VisibleA);
   const bool ExpectedHidden=bActorScope?B.Hidden:(bB?Preset->HiddenInGameB:Preset->HiddenInGameA);
   bOK &= C->GetVisibleFlag()==ExpectedVisible && C->bHiddenInGame==ExpectedHidden;
   if(C->GetWorld() && C->GetWorld()->IsGameWorld()) bOK &= C->ShouldRender()==(ExpectedVisible && !ExpectedHidden && !ExpectedActorHidden);
   if(auto* P=Cast<UPrimitiveComponent>(C)) bOK &= P->CastShadow==(Preset->ShadowPolicy==EURBShadowPolicy::DisableShadows?false:B.CastShadow) && P->bCastHiddenShadow==(Preset->ShadowPolicy==EURBShadowPolicy::DisableHiddenShadows?false:B.CastHiddenShadow);
  }
  if(Out) { ReadVisibility(Out); Out->SetBoolField(TEXT("expectedActorHiddenInGame"),ExpectedActorHidden); }
 }
 if(Out) Out->SetBoolField(TEXT("verified"),bOK);
 if(!bOK) Error=TEXT("Action application readback failed (Material/Scalar/Visibility/Shadow state)");
 return bOK;
}
bool UURBAction::Restore(TSharedPtr<FJsonObject> Out,FString& Error) {
 if(!bSnapshot) { if(Out) { Out->SetBoolField(TEXT("snapshotTaken"),false); Out->SetBoolField(TEXT("restored"),true); } return true; }
 bool bOK=CheckResolved(Error);
 if(Out && Snapshot) Out->SetObjectField(TEXT("original"),Snapshot);
 if(Preset && Preset->ActionType==EURBActionType::ConsoleVariable) return CVar.Restore(Out,Error);
 if(!bOK) { if(Out) Out->SetBoolField(TEXT("restored"),false); return false; }
 if(Preset->ActionType==EURBActionType::ActorVisibility) {
  if(Preset->VisibilityScope==EURBVisibilityScope::Actor) Actor->SetActorHiddenInGame(bOriginalActorHidden);
  for(const auto& B:Visibility) {
   auto* C=B.Component.Get(); if(!IsValid(C)) { bOK=false; continue; }
   if(Preset->VisibilityScope==EURBVisibilityScope::Component) { C->SetVisibility(B.Visible,false); C->SetHiddenInGame(B.Hidden,false); }
   if(auto* P=Cast<UPrimitiveComponent>(C)) { P->SetCastShadow(B.CastShadow); P->SetCastHiddenShadow(B.CastHiddenShadow); }
   bOK &= C->GetVisibleFlag()==B.Visible && C->bHiddenInGame==B.Hidden;
   if(auto* P=Cast<UPrimitiveComponent>(C)) bOK &= P->CastShadow==B.CastShadow && P->bCastHiddenShadow==B.CastHiddenShadow;
  }
  bOK &= Actor->IsHidden()==bOriginalActorHidden;
  if(Out) ReadVisibility(Out);
 } else {
  if(Preset->ActionType==EURBActionType::ScalarParameter && IsValid(DynamicMaterial)) DynamicMaterial->SetScalarParameterValue(Preset->ScalarParameterName,OriginalScalar);
  Mesh->SetMaterial(Preset->MaterialSlot,OriginalMaterial);
  bOK=Mesh->GetMaterial(Preset->MaterialSlot)==OriginalMaterial;
  if(Out) { Out->SetStringField(TEXT("expectedMaterial"),GetPathNameSafe(OriginalMaterial)); Out->SetStringField(TEXT("actualMaterial"),GetActualMaterialPath()); Out->SetBoolField(TEXT("material"),bOK); }
  if(Preset->ActionType==EURBActionType::ScalarParameter) {
   float Actual=0,TransientActual=0;
   const bool bScalar=URBScalarValue(OriginalMaterial,Preset->ScalarParameterName,Actual) && URBSameScalar(Actual,OriginalScalar);
   const bool bTransient=!DynamicMaterial || (URBScalarValue(DynamicMaterial,Preset->ScalarParameterName,TransientActual) && URBSameScalar(TransientActual,OriginalScalar));
   bOK &= bScalar && bTransient;
   if(Out) { Out->SetNumberField(TEXT("originalScalar"),OriginalScalar); Out->SetNumberField(TEXT("actualOriginalScalar"),Actual); Out->SetNumberField(TEXT("actualTransientScalar"),TransientActual); Out->SetBoolField(TEXT("scalar"),bScalar); Out->SetBoolField(TEXT("transientScalar"),bTransient); }
  }
 }
 if(Out) { Out->SetBoolField(TEXT("snapshotTaken"),true); Out->SetBoolField(TEXT("restored"),bOK); }
 if(!bOK) Error=TEXT("Action restoration readback failed");
 return bOK;
}
bool UURBAction::Ready() const {
 if(!Preset) return false;
 if(Preset->ActionType!=EURBActionType::MaterialSwap && Preset->ActionType!=EURBActionType::ScalarParameter) return true;
 return MaterialA && MaterialB && MaterialA->IsComplete() && MaterialB->IsComplete();
}
void UURBAction::PrepareResources() {
#if WITH_EDITOR
 if(MaterialA) MaterialA->EnsureIsComplete(); if(MaterialB && MaterialB!=MaterialA) MaterialB->EnsureIsComplete();
#endif
}
FString UURBAction::GetTargetPath() const { return Preset && Preset->ActionType==EURBActionType::ConsoleVariable?Preset->ConsoleVariableName.ToString():Component?Component->GetPathName():GetPathNameSafe(Actor); }
FString UURBAction::GetActualMaterialPath() const { return Mesh && Preset && Preset->MaterialSlot>=0 && Preset->MaterialSlot<Mesh->GetNumMaterials()?GetPathNameSafe(Mesh->GetMaterial(Preset->MaterialSlot)):TEXT("NotApplicable"); }
void UURBAction::Describe(TSharedPtr<FJsonObject> Out) const {
 if(!Out || !Preset) return;
 Out->SetStringField(TEXT("actionType"),URBActionName(Preset->ActionType)); Out->SetStringField(TEXT("target"),GetTargetPath());
 Out->SetStringField(TEXT("actor"),GetPathNameSafe(Actor)); Out->SetStringField(TEXT("component"),GetPathNameSafe(Component));
 Out->SetBoolField(TEXT("snapshotTaken"),bSnapshot); if(Snapshot) Out->SetObjectField(TEXT("original"),Snapshot);
 if(Preset->ActionType==EURBActionType::MaterialSwap || Preset->ActionType==EURBActionType::ScalarParameter) Out->SetNumberField(TEXT("materialSlot"),Preset->MaterialSlot);
 if(Preset->ActionType==EURBActionType::MaterialSwap) { Out->SetStringField(TEXT("variantA"),GetPathNameSafe(MaterialA)); Out->SetStringField(TEXT("variantB"),GetPathNameSafe(MaterialB)); }
 if(Preset->ActionType==EURBActionType::ScalarParameter) {
  Out->SetStringField(TEXT("parameter"),Preset->ScalarParameterName.ToString()); Out->SetNumberField(TEXT("valueA"),Preset->ScalarValueA); Out->SetNumberField(TEXT("valueB"),Preset->ScalarValueB);
  Out->SetStringField(TEXT("dynamicMaterial"),GetPathNameSafe(DynamicMaterial)); Out->SetNumberField(TEXT("dynamicMaterialObjectID"),DynamicMaterial?DynamicMaterial->GetUniqueID():0); Out->SetBoolField(TEXT("reusesSingleTransientDMI"),true);
 }
 if(Preset->ActionType==EURBActionType::ActorVisibility) {
  Out->SetStringField(TEXT("visibilityScope"),StaticEnum<EURBVisibilityScope>()->GetNameStringByValue((int64)Preset->VisibilityScope));
  Out->SetStringField(TEXT("shadowPolicy"),StaticEnum<EURBShadowPolicy>()->GetNameStringByValue((int64)Preset->ShadowPolicy));
  Out->SetBoolField(TEXT("visibleA"),Preset->VisibleA); Out->SetBoolField(TEXT("visibleB"),Preset->VisibleB); Out->SetBoolField(TEXT("hiddenInGameA"),Preset->HiddenInGameA); Out->SetBoolField(TEXT("hiddenInGameB"),Preset->HiddenInGameB);
  Out->SetBoolField(TEXT("visibleFieldsApplyToComponentOnly"),true); Out->SetBoolField(TEXT("propagateComponentFlagsToChildren"),false); Out->SetBoolField(TEXT("changesFlagsOnChildActorOwnedComponents"),false);
 }
 if(Preset->ActionType==EURBActionType::ConsoleVariable) {
  Out->SetStringField(TEXT("name"),Preset->ConsoleVariableName.ToString()); Out->SetNumberField(TEXT("valueA"),Preset->ConsoleValueA); Out->SetNumberField(TEXT("valueB"),Preset->ConsoleValueB); Out->SetStringField(TEXT("allowlistVersion"),TEXT("UE5.8.3-V1")); CVar.Describe(Out);
 }
}
