#pragma once
#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Materials/MaterialInterface.h"
#include "URBTestPreset.generated.h"

UENUM(BlueprintType)
enum class EURBRunMode : uint8 { StandardBenchmark, CalibrationValidation };

UENUM(BlueprintType)
enum class EURBActionType : uint8 { MaterialSwap, ScalarParameter, ActorVisibility, ConsoleVariable };
UENUM(BlueprintType)
enum class EURBVisibilityScope : uint8 { Actor, Component };
UENUM(BlueprintType)
enum class EURBShadowPolicy : uint8 { PreserveOriginal, DisableShadows, DisableHiddenShadows };

UCLASS(BlueprintType)
class URBENCHMARK_API UURBTestPreset : public UDataAsset {
 GENERATED_BODY()
public:
 UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="01 Test",meta=(ToolTip="결과 폴더와 기록에서 구별할 고유한 Test ID입니다. 새 시험은 다른 ID를 사용하세요.")) FName TestID=TEXT("Material_AB");
 UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="01 Test",meta=(ToolTip="HTML 리포트에 표시할 읽기 쉬운 시험 이름입니다.")) FString TestName=TEXT("Material A/B");
 UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="01 Test",meta=(ToolTip="StandardBenchmark는 실제 A/B를 비교합니다. CalibrationValidation은 A/B 라벨 순서를 유지하되 실제로는 모두 Action A를 적용합니다.")) EURBRunMode RunMode=EURBRunMode::StandardBenchmark;
 UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="01 Test",meta=(EditCondition="RunMode == EURBRunMode::StandardBenchmark",EditConditionHides,ToolTip="켜면 같은 실행에서 A/A Calibration 뒤 A/B를 수집합니다. 기본 Repeat=3일 때 6+6 Capture입니다. 끄면 A/B만 수집합니다.")) bool RunCalibration=false;
 UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="01 Test",meta=(ToolTip="별도 A/A Run ID를 적는 기록용 항목입니다. 자동 연결되지 않으므로 분석 창에서 실제 A/A 결과 폴더를 직접 선택하세요.")) FString CalibrationReferenceRunID;
 UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="01 Test",meta=(ToolTip="한 시험에서 측정할 Action 하나를 선택합니다. 선택한 Action에 필요한 설정만 아래에 표시됩니다.")) EURBActionType ActionType=EURBActionType::MaterialSwap;
 UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="01 Test",meta=(ToolTip="Character, General, Stress 등 장면 종류를 기록합니다. Stress 수치를 실제 게임 비용으로 환산하지 마세요.")) FString SceneType=TEXT("General");
 UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="01 Test",meta=(ToolTip="애니메이션, 조명, 시간 의존 효과와 환경을 통제한 정지 장면일 때만 켜세요. Camera/Transform/Scalability 전후 검사와 별개인 사용자 선언이며 모든 장면 조건의 자동 증명은 아닙니다.")) bool SceneStateDeclaredStatic=false;
 UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="02 Target",meta=(EditCondition="ActionType != EURBActionType::ConsoleVariable",EditConditionHides,ToolTip="대상 Actor의 Actor Tags에 지정합니다. 장면에서 정확히 하나의 Actor와 일치해야 합니다. Component Tags와 다릅니다.")) FName TargetActorTag=TEXT("URB_Target");
 UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="02 Target",meta=(EditCondition="ActionType == EURBActionType::MaterialSwap || ActionType == EURBActionType::ScalarParameter || (ActionType == EURBActionType::ActorVisibility && VisibilityScope == EURBVisibilityScope::Component)",EditConditionHides,ToolTip="대상 Actor 아래 Component의 Component Tags에 지정합니다. 지원되는 Component 정확히 하나와 일치해야 합니다.")) FName TargetComponentTag=TEXT("URB_Mesh");
 UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="02 Target",meta=(ClampMin="0",EditCondition="ActionType == EURBActionType::MaterialSwap || ActionType == EURBActionType::ScalarParameter",EditConditionHides,ToolTip="대상 Mesh의 Material Slot Index입니다. 첫 Slot은 0이며 원래 Material이 있어야 합니다.")) int32 MaterialSlot=0;
 UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="02 Target",meta=(ToolTip="측정 CameraActor의 Actor Tags에 지정합니다. 정확히 하나와 일치해야 하며 측정 중 View Target을 이 Camera로 고정한 뒤 복원합니다.")) FName CameraTag=TEXT("URB_Camera");
 UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="03 MaterialSwap",meta=(EditCondition="ActionType == EURBActionType::MaterialSwap",EditConditionHides,ToolTip="A 상태에 적용할 Material 또는 MIC입니다. Static Switch는 사전에 컴파일한 MIC로 준비하세요. 종료 시 원래 Slot Material을 복원합니다.")) TSoftObjectPtr<UMaterialInterface> VariantA;
 UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="03 MaterialSwap",meta=(EditCondition="ActionType == EURBActionType::MaterialSwap",EditConditionHides,ToolTip="B 상태에 적용할 Material 또는 MIC입니다. StandardBenchmark에서 필요합니다. Production Asset 자체를 수정하지 마세요.")) TSoftObjectPtr<UMaterialInterface> VariantB;
 UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="03 ScalarParameter",meta=(EditCondition="ActionType == EURBActionType::ScalarParameter",EditConditionHides,ToolTip="원래 Slot Material에 정확히 하나 있는 Global Scalar 이름입니다. Layer/Custom Primitive Data 연결 Scalar, Vector, Static Switch는 지원하지 않습니다. 하나의 transient DMI를 재사용한 뒤 원래 값과 Material을 복원합니다.")) FName ScalarParameterName=TEXT("URB_Blend");
 UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="03 ScalarParameter",meta=(EditCondition="ActionType == EURBActionType::ScalarParameter",EditConditionHides,ToolTip="A 상태의 유한한 Scalar 값입니다.")) float ScalarValueA=0;
 UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="03 ScalarParameter",meta=(EditCondition="ActionType == EURBActionType::ScalarParameter",EditConditionHides,ToolTip="B 상태의 유한한 Scalar 값입니다.")) float ScalarValueB=1;
 UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="03 ActorVisibility",meta=(EditCondition="ActionType == EURBActionType::ActorVisibility",EditConditionHides,ToolTip="Actor는 Actor Hidden In Game을 변경합니다. Component는 지정 Component의 Visible/Hidden In Game을 변경하며 자식으로 전파하지 않습니다. Child Actor 대상은 지원하지 않습니다.")) EURBVisibilityScope VisibilityScope=EURBVisibilityScope::Component;
 UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="03 ActorVisibility",meta=(EditCondition="ActionType == EURBActionType::ActorVisibility && VisibilityScope == EURBVisibilityScope::Component",EditConditionHides,ToolTip="A 상태의 Component Visible Flag입니다. Actor/Component Hidden In Game도 별도로 표시 여부에 영향을 줍니다.")) bool VisibleA=true;
 UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="03 ActorVisibility",meta=(EditCondition="ActionType == EURBActionType::ActorVisibility && VisibilityScope == EURBVisibilityScope::Component",EditConditionHides,ToolTip="B 상태의 Component Visible Flag입니다. true만으로 게임 표시를 보장하지 않습니다.")) bool VisibleB=false;
 UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="03 ActorVisibility",meta=(EditCondition="ActionType == EURBActionType::ActorVisibility",EditConditionHides,ToolTip="A 상태의 Hidden In Game입니다. Actor Scope는 Actor, Component Scope는 지정 Component에 적용합니다.")) bool HiddenInGameA=false;
 UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="03 ActorVisibility",meta=(EditCondition="ActionType == EURBActionType::ActorVisibility",EditConditionHides,ToolTip="B 상태의 Hidden In Game입니다. 숨김만으로 모든 Shadow 비용이 없어지지는 않습니다.")) bool HiddenInGameB=true;
 UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="03 ActorVisibility",meta=(EditCondition="ActionType == EURBActionType::ActorVisibility",EditConditionHides,ToolTip="원래 Shadow 유지, Cast Shadow 비활성화, Cast Hidden Shadow 비활성화 중 선택합니다. Actor Scope는 해당 Actor 소유 Primitive Component, Component Scope는 지정 대상에만 적용하고 원래 Flag를 복원합니다.")) EURBShadowPolicy ShadowPolicy=EURBShadowPolicy::PreserveOriginal;
 UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="03 ConsoleVariable",meta=(EditCondition="ActionType == EURBActionType::ConsoleVariable",EditConditionHides,GetOptions="GetAllowedConsoleVariables",ToolTip="허용된 Runtime CVar만 선택합니다. r.Tonemapper.Sharpen: 유한한 0~10 실수. r.BloomQuality: 0~5 정수. 원래 값/우선순위/태그를 복원합니다.")) FName ConsoleVariableName=TEXT("r.Tonemapper.Sharpen");
 UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="03 ConsoleVariable",meta=(EditCondition="ActionType == EURBActionType::ConsoleVariable",EditConditionHides,ToolTip="A 상태의 CVar 값입니다. 선택한 CVar의 허용 범위와 정수 조건을 지켜야 합니다.")) float ConsoleValueA=0;
 UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="03 ConsoleVariable",meta=(EditCondition="ActionType == EURBActionType::ConsoleVariable",EditConditionHides,ToolTip="B 상태의 CVar 값입니다. 적용 후 실제 값과 설정 우선순위를 확인합니다.")) float ConsoleValueB=1;
 UFUNCTION() TArray<FString> GetAllowedConsoleVariables() const { return {TEXT("r.Tonemapper.Sharpen"),TEXT("r.BloomQuality")}; }
 UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="04 Capture",meta=(ClampMin="1",ToolTip="각 Capture 전에 상태 적용과 준비가 끝난 뒤 기다리는 프레임 수입니다. 기본 120이며 수집 프레임에 포함하지 않습니다.")) int32 WarmupFrames=120;
 UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="04 Capture",meta=(ClampMin="1",ToolTip="각 CSV에 수집할 프레임 수입니다. 기본 300이며 저장 완료와 유효 프레임 수를 검증합니다.")) int32 CaptureFrames=300;
 UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="04 Capture",meta=(ClampMin="1",ClampMax="50",ToolTip="Variant별 반복 횟수입니다. 기본 3이면 A/B 총 6 Capture입니다. 3회 미만은 확정 비교 판정을 보류합니다.")) int32 RepeatCount=3;
 UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="04 Capture",meta=(ToolTip="Standalone 측정 해상도입니다. 임시 적용한 실제 창 크기를 확인하고 종료 시 원래 크기를 복원합니다.")) FIntPoint Resolution=FIntPoint(1920,1080);
 UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="04 Capture",meta=(ClampMin="10",ClampMax="200",ToolTip="측정 중 임시 적용할 r.ScreenPercentage입니다. 기본 100%이며 종료 시 원래 값과 우선순위를 복원합니다.")) float ScreenPercentage=100;
 UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="04 Capture",meta=(ClampMin="1",ToolTip="성능 리포트의 프레임 예산 계산용입니다. 60이면 16.667ms이며 실제 측정 FPS를 제한하지 않습니다.")) int32 TargetFPS=60;
};
