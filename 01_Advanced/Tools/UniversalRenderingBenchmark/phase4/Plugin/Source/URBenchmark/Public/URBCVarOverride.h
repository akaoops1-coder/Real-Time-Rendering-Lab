#pragma once
#include "CoreMinimal.h"
class FJsonObject;

/** Owns one temporary 5.8 CVar history entry; preserves underlying priority/tag. */
struct URBENCHMARK_API FURBCVarOverride {
 FString Name,OriginalValue,AppliedValue;
 uint32 OriginalPriority=0,OriginalFlags=0;
 FName OriginalTag,TemporaryTag;
 bool bSnapshot=false,bApplied=false,bTemporary=true;
 bool Snapshot(const FString& InName,FString& Error);
 bool Begin(const FString& InName,const FString& Value,FString& Error);
 bool Set(const FString& Value,FString& Error);
 bool Verify(const FString& ExpectedValue,TSharedPtr<FJsonObject> Out,FString& Error) const;
 bool Restore(TSharedPtr<FJsonObject> Out,FString& Error);
 bool IsRestored() const;
 void Describe(TSharedPtr<FJsonObject> Out) const;
};
