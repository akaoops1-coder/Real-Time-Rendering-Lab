#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"
#include "URBTestTarget.generated.h"

// Fixture for the separate benchmark level; the Runner accepts ordinary mesh actors too.
UCLASS()
class URBENCHMARK_API AURBTestTarget : public AActor {
 GENERATED_BODY()
public:
 AURBTestTarget() {
  PrimaryMesh=CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PrimaryMesh")); SetRootComponent(PrimaryMesh);
  PrimaryMesh->SetMobility(EComponentMobility::Movable);
  PrimaryMesh->ComponentTags={TEXT("URB_Mesh"),TEXT("URB_DuplicateComponent")};
  SecondaryMesh=CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SecondaryMesh")); SecondaryMesh->SetupAttachment(PrimaryMesh);
  SecondaryMesh->ComponentTags={TEXT("URB_Secondary"),TEXT("URB_DuplicateComponent")}; SecondaryMesh->SetHiddenInGame(true);
  Tags={TEXT("URB_Target")};
 }
 UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category="Test Fixture") TObjectPtr<UStaticMeshComponent> PrimaryMesh;
 UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category="Test Fixture") TObjectPtr<UStaticMeshComponent> SecondaryMesh;
};
