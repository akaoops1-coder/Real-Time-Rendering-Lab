#pragma once
#include "CoreMinimal.h"
class FJsonObject;
class ACameraActor;
class UURBTestPreset;
class UWorld;

/** Read-only provenance collection. Call only outside CSV capture. */
struct FURBMetadata {
 static FString SHA256(const TArray<uint8>& Bytes);
 static FString SHA256Text(const FString& Text);
 static FString FileSHA256(const FString& Path);
 static FString ContentSHA256(TSharedPtr<FJsonObject> Index);
 static TSharedRef<FJsonObject> Invariants(UWorld* World,ACameraActor* Camera);
 static FString Json(const TSharedRef<FJsonObject>& Object);
 static TSharedRef<FJsonObject> Fingerprint(UURBTestPreset* Preset,UWorld* World,ACameraActor* Camera,const FString& ContentHash,const TSharedRef<FJsonObject>& Invariants,TSharedPtr<FJsonObject> ActionDescription);
};
