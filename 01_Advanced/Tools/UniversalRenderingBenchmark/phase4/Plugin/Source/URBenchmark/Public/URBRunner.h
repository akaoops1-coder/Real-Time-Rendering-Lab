#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "URBTestPreset.h"
#include "URBCaptureComponent.h"
#include "URBCVarOverride.h"
#include "URBRunner.generated.h"

UENUM(BlueprintType)
enum class EURBRunState : uint8 { IDLE,VALIDATING,PREPARING,WARMUP,CAPTURING,RESTORING,COMPLETED,FAILED,CANCELLED };

UCLASS(Blueprintable)
class URBENCHMARK_API AURBRunner : public AActor {
 GENERATED_BODY()
public:
 AURBRunner();
 virtual void BeginPlay() override;
 virtual void Tick(float DeltaSeconds) override;
 virtual void EndPlay(const EEndPlayReason::Type Reason) override;
 UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="URB Configuration",meta=(ToolTip="실행할 URBTestPreset을 선택합니다. 예제 Preset을 복제하면 Runner 코드 수정 없이 새 Action 시험을 추가할 수 있습니다.")) TObjectPtr<UURBTestPreset> Preset;
 UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="URB Configuration",meta=(ToolTip="켜면 Unreal 기본 Play 메뉴의 Standalone Game 시작 시 자동 측정합니다. 선택을 바꾼 Benchmark 전용 Level과 Preset만 저장하세요.")) bool AutoRunOnBeginPlay=true;
 UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category="URB Capture",meta=(ToolTip="CSV 수집과 파일 쓰기 완료/유효 프레임 검증을 담당하는 내부 Component입니다.")) TObjectPtr<UURBCaptureComponent> Capture;
 UPROPERTY(Transient,VisibleAnywhere,BlueprintReadOnly,Category="URB Status",meta=(ToolTip="현재 실행 상태입니다. 정상 완료는 COMPLETED이며 실패/취소와 구별하세요.")) EURBRunState State=EURBRunState::IDLE;
 UPROPERTY(Transient,VisibleAnywhere,BlueprintReadOnly,Category="URB Status",meta=(ToolTip="검증 결과 또는 현재 상태/오류 원인입니다. 자세한 기록은 Output Log와 결과 폴더의 Execution.log를 확인하세요.")) FString LastMessage;
 UPROPERTY(Transient,VisibleAnywhere,BlueprintReadOnly,Category="URB Status",meta=(ToolTip="이번 Run의 Raw, Manifest.json, Completion.json 저장 폴더입니다. 완료 후 Analyze.cmd에서 이 Run 폴더를 선택하세요.")) FString OutputDirectory;
 UFUNCTION(BlueprintCallable,CallInEditor,Category="URB",meta=(ToolTip="측정 전에 Preset, Action 지원, Tag의 유일한 대상, Slot과 Camera를 확인합니다. 실제 Capture와 복원 검증은 Standalone에서 수행합니다.")) void ValidatePreset();
 UFUNCTION(BlueprintCallable,Category="URB",meta=(ToolTip="Preset에 지정된 측정을 시작합니다. 일반 사용자는 Auto Run과 Standalone Game을 사용하세요.")) void StartBenchmark();
 UFUNCTION(BlueprintCallable,Category="URB",meta=(ToolTip="측정 중 Esc와 같은 안전 취소를 요청합니다. CSV 쓰기 완료와 원상 복구를 기다리며 강제 종료와 다릅니다.")) void CancelBenchmark();
private:
 UPROPERTY(Transient) TObjectPtr<UURBTestPreset> Active;
 UPROPERTY(Transient) TObjectPtr<class UURBAction> Action;
 UPROPERTY(Transient) TObjectPtr<class ACameraActor> Camera;
 UPROPERTY(Transient) TObjectPtr<AActor> OriginalViewTarget;
 TArray<FURBCVarOverride> SavedCVars;
 TArray<bool> Sequence;
 TArray<TSharedPtr<class FJsonValue>> Records;
 TSharedPtr<class FJsonObject> Manifest;
 int32 CaptureIndex=0,FrameCounter=0,PrepareStage=0,OriginalWindowMode=0;
 FIntPoint OriginalResolution=FIntPoint::ZeroValue;
 double StageStart=0,FinishedAt=0,LastPrepareLog=0;
 FString RunID,Scenario,FinishReason;
 FString ContentSnapshotHash,InvariantSnapshotJSON;
 EURBRunState FinalState=EURBRunState::COMPLETED;
 bool bOriginalSaved=false,bCancelPending=false,bAutoExit=false,bFaultUsed=false,bRestorationApplied=false,bEnding=false,bPendingAutoStart=false;
 bool bScreenMessagesBackedUp=false,bOriginalScreenMessages=true,bActionRestored=true;
 bool Resolve(FString& Error);
 bool Ready() const;
 bool IsCalibrationCapture() const;
 bool CheckInvariants() const;
 bool ApplyAction(bool bB,FString& Error);
 void SetState(EURBRunState NewState,const FString& Message);
 void Log(const FString& Message);
 void SaveManifest();
 void SetupEnvironment();
 void BeginNextCapture();
 void BeginRestore(EURBRunState Result,const FString& Reason);
 void FinishRestore();
 bool SetTemporaryCVar(const TCHAR* Name,const FString& Value);
 UFUNCTION() void CaptureFinished(bool bSuccess,const FString& Filename,const FString& Error);
};
