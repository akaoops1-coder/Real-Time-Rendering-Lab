#include "URBCaptureComponent.h"

#include "Async/Async.h"
#include "HAL/FileManager.h"
#include "HAL/PlatformTime.h"
#include "Misc/FileHelper.h"
#include "String/LexFromString.h"
#include "Misc/Paths.h"
#include "ProfilingDebugging/CsvProfiler.h"
#include "Serialization/Csv/CsvParser.h"

namespace
{
    // FCsvProfiler is process-global. Reserve it across URB helper instances before its queued Start is processed.
    TWeakObjectPtr<UURBCaptureComponent> CaptureOwner;

    FString NormalizedFilename(const FString& Filename)
    {
        FString Result = FPaths::ConvertRelativePathToFull(Filename);
        FPaths::NormalizeFilename(Result);
        FPaths::CollapseRelativeDirectories(Result);
        return Result;
    }

    bool SameFilename(const FString& A, const FString& B)
    {
        return NormalizedFilename(A).Equals(NormalizedFilename(B), ESearchCase::IgnoreCase);
    }

    bool IsMetadataRecord(const FCsvParser::FRows::ElementType& Row)
    {
        if (Row.Num() < 2 || Row.Num() % 2 != 0)
        {
            return false;
        }
        for (int32 Index = 0; Index < Row.Num(); Index += 2)
        {
            const FString Key(Row[Index]);
            if (!Key.StartsWith(TEXT("[")) || !Key.EndsWith(TEXT("]")))
            {
                return false;
            }
        }
        return true;
    }

    bool ParseTimingCell(const TCHAR* Cell, double& OutValue)
    {
        const FString Text = FString(Cell).TrimStartAndEnd();
        int32 Index = 0;
        if (Index < Text.Len() && (Text[Index] == TEXT('+') || Text[Index] == TEXT('-')))
        {
            ++Index;
        }
        bool bSawDigit = false;
        while (Index < Text.Len() && FChar::IsDigit(Text[Index]))
        {
            bSawDigit = true;
            ++Index;
        }
        if (Index < Text.Len() && Text[Index] == TEXT('.'))
        {
            ++Index;
            while (Index < Text.Len() && FChar::IsDigit(Text[Index]))
            {
                bSawDigit = true;
                ++Index;
            }
        }
        if (!bSawDigit)
        {
            return false;
        }
        if (Index < Text.Len() && (Text[Index] == TEXT('e') || Text[Index] == TEXT('E')))
        {
            ++Index;
            if (Index < Text.Len() && (Text[Index] == TEXT('+') || Text[Index] == TEXT('-')))
            {
                ++Index;
            }
            const int32 ExponentStart = Index;
            while (Index < Text.Len() && FChar::IsDigit(Text[Index]))
            {
                ++Index;
            }
            if (Index == ExponentStart)
            {
                return false;
            }
        }
        return Index == Text.Len() && LexTryParseString(OutValue, *Text) && FMath::IsFinite(OutValue);
    }
}

UURBCaptureComponent::UURBCaptureComponent()
{
    PrimaryComponentTick.bCanEverTick = true;
    PrimaryComponentTick.bStartWithTickEnabled = false;
    PrimaryComponentTick.bTickEvenWhenPaused = true;
}

bool UURBCaptureComponent::StartCapture(int32 Frames, const FString& Folder, const FString& Filename, const TMap<FString, FString>& Metadata)
{
    if (!IsInGameThread())
    {
        return false;
    }
    if (bBusy)
    {
        LastError = TEXT("CaptureAlreadyInProgress");
        return false;
    }
    LastError.Reset();
    LastCaptureFilename.Reset();
    ValidFrameCount = 0;
    if (Frames <= 0 || Folder.IsEmpty() || Filename.IsEmpty() || FPaths::GetCleanFilename(Filename) != Filename || FPaths::MakeValidFileName(Filename) != Filename)
    {
        LastError = TEXT("InvalidCaptureArguments");
        return false;
    }
    for (const TPair<FString, FString>& Pair : Metadata)
    {
        if (Pair.Key.IsEmpty() || Pair.Key.Contains(TEXT(",")) || Pair.Key.Contains(TEXT("\n")) || Pair.Key.Contains(TEXT("\r")))
        {
            LastError = TEXT("InvalidCaptureMetadataKey");
            return false;
        }
    }
    if (CaptureOwner.IsValid() && CaptureOwner.Get() != this && CaptureOwner->IsBusy())
    {
        LastError = TEXT("AnotherURBCaptureInProgress");
        return false;
    }
    FCsvProfiler* Profiler = FCsvProfiler::Get();
    if (!Profiler || FCsvProfiler::IsCapturing() || Profiler->IsWritingFile() || Profiler->IsEndCapturePending())
    {
        LastError = TEXT("CsvProfilerBusyOrUnavailable");
        return false;
    }
    const FString DestinationFolder = NormalizedFilename(Folder);
    const FString CsvFilename = FPaths::SetExtension(Filename, TEXT("csv"));
    RequestedFilename = NormalizedFilename(DestinationFolder / CsvFilename);
    if (IFileManager::Get().FileExists(*RequestedFilename))
    {
        LastError = TEXT("CaptureFileAlreadyExists");
        return false;
    }
    if (!IFileManager::Get().MakeDirectory(*DestinationFolder, true) && !IFileManager::Get().DirectoryExists(*DestinationFolder))
    {
        LastError = TEXT("CaptureDirectoryUnavailable");
        return false;
    }
    if (!ProfilerFinishedHandle.IsValid())
    {
        const TWeakObjectPtr<UURBCaptureComponent> WeakThis(this);
        ProfilerFinishedHandle = Profiler->OnCSVProfileFinished().AddLambda([WeakThis](const FString& FinishedFile)
        {
            // The profiler may broadcast from its writer thread; the weak reference was created on the game thread.
            AsyncTask(ENamedThreads::GameThread, [WeakThis, FinishedFile]()
            {
                if (UURBCaptureComponent* Self = WeakThis.Get())
                {
                    Self->AcceptFinishedOnGameThread(FinishedFile);
                }
            });
        });
    }
    RequestedFrames = Frames;
    bCancellationRequested = false;
    bStopRequested = false;
    bSawOwnedCapture = false;
    bFinishedCallbackReceived = false;
    bTimedOut = false;
    FinishedFilename.Reset();
    StartedAtSeconds = FPlatformTime::Seconds();
    TimedOutAtSeconds = 0.0;
    bBusy = true;
    CaptureOwner = this;
    ActiveMetadataKeys.Reset();
    for (const TPair<FString, FString>& Pair : Metadata)
    {
        ActiveMetadataKeys.Add(Pair.Key);
        FCsvProfiler::SetNonPersistentMetadata(*Pair.Key, *Pair.Value);
    }
    SetComponentTickEnabled(true);
    // Queued by the engine; a successful request is not yet a successful capture.
    Profiler->BeginCapture(Frames, DestinationFolder, CsvFilename);
    return true;
}

void UURBCaptureComponent::AcceptFinishedOnGameThread(const FString& Filename)
{
    if (bBusy && SameFilename(Filename, RequestedFilename))
    {
        bFinishedCallbackReceived = true;
        FinishedFilename = NormalizedFilename(Filename);
    }
}

void UURBCaptureComponent::RequestOwnedCaptureStop()
{
    FCsvProfiler* Profiler = FCsvProfiler::Get();
    if (!bStopRequested && Profiler && FCsvProfiler::IsCapturing() && SameFilename(Profiler->GetOutputFilename(), RequestedFilename))
    {
        bSawOwnedCapture = true;
        bStopRequested = true;
        Profiler->EndCapture();
    }
}

void UURBCaptureComponent::CancelCapture()
{
    if (IsInGameThread() && bBusy)
    {
        bCancellationRequested = true;
        // If Start is still queued, Tick waits for our filename before stopping it.
        RequestOwnedCaptureStop();
    }
}

void UURBCaptureComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
    if (!bBusy)
    {
        return;
    }
    FCsvProfiler* Profiler = FCsvProfiler::Get();
    if (!Profiler)
    {
        Finish(false, TEXT("CsvProfilerUnavailable"));
        return;
    }
    const bool bProfilerCapturing = FCsvProfiler::IsCapturing();
    if (bProfilerCapturing)
    {
        if (!SameFilename(Profiler->GetOutputFilename(), RequestedFilename))
        {
            // Do not stop an unrelated capture even if it started between our request and BeginFrame.
            Finish(false, TEXT("UnexpectedExternalCsvCapture"));
            return;
        }
        bSawOwnedCapture = true;
    }
    const double Now = FPlatformTime::Seconds();
    if (!bTimedOut && Now - StartedAtSeconds > FMath::Max(1.0, static_cast<double>(CaptureTimeoutSeconds)))
    {
        bTimedOut = true;
        TimedOutAtSeconds = Now;
    }
    if (bCancellationRequested || bTimedOut)
    {
        RequestOwnedCaptureStop();
    }
    const bool bProfilerIdle = !FCsvProfiler::IsCapturing() && !Profiler->IsWritingFile() && !Profiler->IsEndCapturePending();
    if (bFinishedCallbackReceived && bProfilerIdle)
    {
        LastCaptureFilename = FinishedFilename;
        FString ValidationError;
        const bool bValid = ValidateCsv(FinishedFilename, ValidationError);
        if (bTimedOut)
        {
            Finish(false, TEXT("CaptureTimeout"));
        }
        else if (bCancellationRequested)
        {
            Finish(false, TEXT("Cancelled"));
        }
        else
        {
            Finish(bValid, ValidationError);
        }
        return;
    }
    if (bTimedOut && (bProfilerIdle || Now - TimedOutAtSeconds > 10.0))
    {
        // The caller can restore on failure. A lingering engine writer is never reported as success.
        Finish(false, bProfilerIdle ? TEXT("CaptureTimeoutNoCompletedFile") : TEXT("CaptureTimeoutProfilerStillBusy"));
        return;
    }
    if (!bSawOwnedCapture && !bFinishedCallbackReceived && bProfilerIdle && Now - StartedAtSeconds > 10.0)
    {
        Finish(false, bCancellationRequested ? TEXT("CancelledBeforeCaptureStarted") : TEXT("CaptureDidNotStart"));
    }
}

bool UURBCaptureComponent::ValidateCsv(const FString& Filename, FString& OutError)
{
    ValidFrameCount = 0;
    FString Source;
    if (!FFileHelper::LoadFileToString(Source, *Filename) || Source.IsEmpty())
    {
        OutError = TEXT("CaptureFileMissingOrEmpty");
        return false;
    }
    const FCsvParser Parser(MoveTemp(Source));
    const FCsvParser::FRows& Rows = Parser.GetRows();
    if (Rows.IsEmpty())
    {
        OutError = TEXT("CsvHeaderMissing");
        return false;
    }
    const TCHAR* Required[] = { TEXT("FrameTime"), TEXT("GameThreadTime"), TEXT("RenderThreadTime"), TEXT("GPUTime") };
    int32 Indices[4] = { INDEX_NONE, INDEX_NONE, INDEX_NONE, INDEX_NONE };
    for (int32 Column = 0; Column < Rows[0].Num(); ++Column)
    {
        for (int32 Metric = 0; Metric < 4; ++Metric)
        {
            if (FCString::Strcmp(Rows[0][Column], Required[Metric]) == 0)
            {
                if (Indices[Metric] != INDEX_NONE)
                {
                    OutError = FString::Printf(TEXT("DuplicateMetricColumn:%s"), Required[Metric]);
                    return false;
                }
                Indices[Metric] = Column;
            }
        }
    }
    for (int32 Metric = 0; Metric < 4; ++Metric)
    {
        if (Indices[Metric] == INDEX_NONE)
        {
            OutError = FString::Printf(TEXT("RequiredMetricMissing:%s"), Required[Metric]);
            return false;
        }
    }
    for (int32 RowIndex = 1; RowIndex < Rows.Num(); ++RowIndex)
    {
        const auto& Row = Rows[RowIndex];
        if (Row.IsEmpty() || (Row.Num() == 1 && FCString::Strlen(Row[0]) == 0) || IsMetadataRecord(Row))
        {
            continue;
        }
        bool bRepeatedHeader = true;
        for (int32 Metric = 0; Metric < 4; ++Metric)
        {
            bRepeatedHeader &= Row.IsValidIndex(Indices[Metric]) && FCString::Strcmp(Row[Indices[Metric]], Required[Metric]) == 0;
        }
        if (bRepeatedHeader)
        {
            continue;
        }
        double Values[4] = {};
        for (int32 Metric = 0; Metric < 4; ++Metric)
        {
            if (!Row.IsValidIndex(Indices[Metric]) || !ParseTimingCell(Row[Indices[Metric]], Values[Metric]))
            {
                OutError = FString::Printf(TEXT("InvalidMetricSample:row=%d,metric=%s"), RowIndex + 1, Required[Metric]);
                return false;
            }
        }
        if (Values[0] <= 0.0 || Values[1] < 0.0 || Values[2] < 0.0 || Values[3] <= 0.0)
        {
            OutError = FString::Printf(TEXT("InvalidTimingOrMissingGpu:row=%d"), RowIndex + 1);
            return false;
        }
        ++ValidFrameCount;
    }
    if (ValidFrameCount != RequestedFrames)
    {
        OutError = FString::Printf(TEXT("CaptureFrameCountMismatch:expected=%d,actual=%d"), RequestedFrames, ValidFrameCount);
        return false;
    }
    OutError.Reset();
    return true;
}

void UURBCaptureComponent::Finish(bool bSuccess, const FString& Error)
{
    if (!bBusy)
    {
        return;
    }
    const FString ResultFilename = LastCaptureFilename.IsEmpty() ? RequestedFilename : LastCaptureFilename;
    LastCaptureFilename = ResultFilename;
    LastError = Error;
    ClearCaptureMetadata();
    bBusy = false;
    SetComponentTickEnabled(false);
    if (CaptureOwner.Get() == this)
    {
        CaptureOwner.Reset();
    }
    OnCaptureFinished.Broadcast(bSuccess, ResultFilename, Error);
}

void UURBCaptureComponent::ClearCaptureMetadata()
{
    for (const FString& Key : ActiveMetadataKeys)
    {
        FCsvProfiler::SetNonPersistentMetadata(*Key, nullptr);
    }
    ActiveMetadataKeys.Reset();
}

void UURBCaptureComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
    if (bBusy)
    {
        bCancellationRequested = true;
        RequestOwnedCaptureStop();
    }
    if (ProfilerFinishedHandle.IsValid())
    {
        if (FCsvProfiler* Profiler = FCsvProfiler::Get())
        {
            Profiler->OnCSVProfileFinished().Remove(ProfilerFinishedHandle);
        }
        ProfilerFinishedHandle.Reset();
    }
    if (CaptureOwner.Get() == this)
    {
        CaptureOwner.Reset();
    }
    ClearCaptureMetadata();
    bBusy = false;
    Super::EndPlay(EndPlayReason);
}
