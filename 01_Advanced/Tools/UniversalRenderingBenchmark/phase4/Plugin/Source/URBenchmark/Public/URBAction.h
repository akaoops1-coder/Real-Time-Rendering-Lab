#pragma once
#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "URBTestPreset.h"
#include "URBCVarOverride.h"
#include "URBAction.generated.h"

class FJsonObject;
class USceneComponent;
class UMeshComponent;
class UMaterialInstanceDynamic;
class UWorld;

USTRUCT()
struct FURBVisibilityBackup {
 GENERATED_BODY()
 UPROPERTY(Transient) TObjectPtr<USceneComponent> Component;
 bool Visible=false, Hidden=false, CastShadow=false, CastHiddenShadow=false;
};

/** Per-run transient action state. Never changes or saves a Material asset. */
UCLASS()
class URBENCHMARK_API UURBAction : public UObject {
 GENERATED_BODY()
public:
 bool Resolve(UURBTestPreset* InPreset,UWorld* World,FString& Error);
 bool SnapshotAndPrepare(FString& Error);
 bool Apply(bool bVariantB,FString& Error);
 bool Verify(bool bVariantB,TSharedPtr<FJsonObject> Out,FString& Error) const;
 bool Restore(TSharedPtr<FJsonObject> Out,FString& Error);
 bool Ready() const;
 void PrepareResources();
 void Describe(TSharedPtr<FJsonObject> Out) const;
 FString GetTargetPath() const;
 FString GetActualMaterialPath() const;
 bool HasSnapshot() const { return bSnapshot; }
private:
 UPROPERTY(Transient) TObjectPtr<UURBTestPreset> Preset;
 UPROPERTY(Transient) TObjectPtr<AActor> Actor;
 UPROPERTY(Transient) TObjectPtr<USceneComponent> Component;
 UPROPERTY(Transient) TObjectPtr<UMeshComponent> Mesh;
 UPROPERTY(Transient) TObjectPtr<UMaterialInterface> MaterialA;
 UPROPERTY(Transient) TObjectPtr<UMaterialInterface> MaterialB;
 UPROPERTY(Transient) TObjectPtr<UMaterialInterface> OriginalMaterial;
 UPROPERTY(Transient) TObjectPtr<UMaterialInstanceDynamic> DynamicMaterial;
 UPROPERTY(Transient) TArray<FURBVisibilityBackup> Visibility;
 bool bSnapshot=false,bOriginalActorHidden=false;
 float OriginalScalar=0;
 FURBCVarOverride CVar;
 TSharedPtr<FJsonObject> Snapshot;
 bool CheckResolved(FString& Error) const;
 void ReadVisibility(TSharedPtr<FJsonObject> Out) const;
};
