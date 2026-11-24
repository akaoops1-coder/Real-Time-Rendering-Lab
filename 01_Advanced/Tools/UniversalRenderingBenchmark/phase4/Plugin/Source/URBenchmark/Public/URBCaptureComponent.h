#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "URBCaptureComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FURBCaptureFinished, bool, bSuccess, const FString&, Filename, const FString&, Error);

/** CSV mechanics only. The Runner owns test order, Materials and restoration. */
UCLASS(ClassGroup=(URBenchmark), meta=(BlueprintSpawnableComponent))
class URBENCHMARK_API UURBCaptureComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    UURBCaptureComponent();

    /** False is a synchronous validation failure; read LastError. True completes through OnCaptureFinished. */
    UFUNCTION(BlueprintCallable, Category="URBenchmark|Capture")
    bool StartCapture(int32 Frames, const FString& Folder, const FString& Filename, const TMap<FString, FString>& Metadata);

    /** Ends only this component's capture and waits for asynchronous writing before completion. */
    UFUNCTION(BlueprintCallable, Category="URBenchmark|Capture")
    void CancelCapture();

    UFUNCTION(BlueprintPure, Category="URBenchmark|Capture")
    bool IsBusy() const { return bBusy; }

    UPROPERTY(BlueprintAssignable, Category="URBenchmark|Capture")
    FURBCaptureFinished OnCaptureFinished;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="URBenchmark|Capture", meta=(ClampMin="1.0", UIMin="1.0"))
    float CaptureTimeoutSeconds = 120.0f;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="URBenchmark|Capture")
    FString LastError;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="URBenchmark|Capture")
    FString LastCaptureFilename;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="URBenchmark|Capture")
    int32 ValidFrameCount = 0;

protected:
    virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
    virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
    bool bBusy = false;
    bool bCancellationRequested = false;
    bool bStopRequested = false;
    bool bSawOwnedCapture = false;
    bool bFinishedCallbackReceived = false;
    bool bTimedOut = false;
    int32 RequestedFrames = 0;
    double StartedAtSeconds = 0.0;
    double TimedOutAtSeconds = 0.0;
    FString RequestedFilename;
    FString FinishedFilename;
    TArray<FString> ActiveMetadataKeys;
    FDelegateHandle ProfilerFinishedHandle;

    void AcceptFinishedOnGameThread(const FString& Filename);
    void RequestOwnedCaptureStop();
    void ClearCaptureMetadata();
    void Finish(bool bSuccess, const FString& Error);
    bool ValidateCsv(const FString& Filename, FString& OutError);
};
