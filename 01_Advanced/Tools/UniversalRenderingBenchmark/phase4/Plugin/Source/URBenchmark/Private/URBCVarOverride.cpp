#include "URBCVarOverride.h"
#include "HAL/IConsoleManager.h"
#include "Dom/JsonObject.h"

static FName URBCurrentCVarTag(IConsoleVariable* C) {
 // Tag-only query: never attempts to replace the immutable Constructor layer.
 IConsoleVariable::FSetContext Query((EConsoleVariableFlags)(C->GetFlags()&ECVF_SetByMask),NAME_None);
 Query.TagMode=IConsoleVariable::FSetContext::ETagMode::ReplaceCurrent;
 Query.MinPriority=ECVF_SetByConstructor;
 return C->ResolveContext(Query).Tag;
}
bool FURBCVarOverride::Snapshot(const FString& InName,FString& Error) {
 if(bSnapshot) { Error=TEXT("CVar state was already snapshotted"); return false; }
 auto* C=IConsoleManager::Get().FindConsoleVariable(*InName);
 if(!C || C->TestFlags((EConsoleVariableFlags)(ECVF_ReadOnly|ECVF_Unregistered|ECVF_CreatedFromIni))) { Error=TEXT("UNSUPPORTED: CVar is absent, unregistered, read-only or unresolved"); return false; }
 Name=InName; OriginalValue=C->GetString(); OriginalFlags=(uint32)C->GetFlags();
 OriginalPriority=OriginalFlags&(uint32)ECVF_SetByMask; OriginalTag=URBCurrentCVarTag(C);
 if(OriginalPriority>(uint32)ECVF_SetByConsole) { Error=TEXT("UNSUPPORTED: unknown CVar source priority"); return false; }
 bTemporary=OriginalPriority<=(uint32)ECVF_SetByTemp;
 TemporaryTag=FName(*(TEXT("URBenchmark_")+FGuid::NewGuid().ToString(EGuidFormats::Digits)));
 bSnapshot=true; return true;
}
bool FURBCVarOverride::Begin(const FString& InName,const FString& Value,FString& Error) { return Snapshot(InName,Error) && Set(Value,Error); }
bool FURBCVarOverride::Set(const FString& Value,FString& Error) {
 auto* C=IConsoleManager::Get().FindConsoleVariable(*Name);
 if(!bSnapshot || !C) { Error=TEXT("CVar snapshot or variable missing"); return false; }
 if(bTemporary) {
  IConsoleVariable::FSetContext Context(ECVF_SetByTemp,TemporaryTag);
  Context.TagMode=IConsoleVariable::FSetContext::ETagMode::Replace;
  C->Set(*Value,Context);
 } else {
  // Console is above Temp. Explicitly replace only its snapshotted layer/tag.
  C->Set(*Value,IConsoleVariable::FResolvedContext{(EConsoleVariableFlags)OriginalPriority,OriginalTag});
 }
 bApplied=true; AppliedValue=Value; return Verify(Value,nullptr,Error);
}
bool FURBCVarOverride::Verify(const FString& ExpectedValue,TSharedPtr<FJsonObject> Out,FString& Error) const {
 auto* C=IConsoleManager::Get().FindConsoleVariable(*Name);
 double Expected=0;
 const bool bNumeric=LexTryParseString(Expected,*ExpectedValue) && FMath::IsFinite(Expected);
 const uint32 Priority=C?((uint32)C->GetFlags()&(uint32)ECVF_SetByMask):0;
 const FName Tag=C?URBCurrentCVarTag(C):NAME_None;
 const uint32 ExpectedPriority=bTemporary?(uint32)ECVF_SetByTemp:OriginalPriority;
 const FName ExpectedTag=bTemporary?TemporaryTag:OriginalTag;
 const bool bValue=C && bNumeric && FMath::IsNearlyEqual((double)C->GetFloat(),Expected,FMath::Max(1.e-5,FMath::Abs(Expected)*1.e-6));
 const bool bMatch=bSnapshot && bApplied && C && bValue && Priority==ExpectedPriority && Tag==ExpectedTag;
 if(Out) {
  Out->SetStringField(TEXT("name"),Name); Out->SetStringField(TEXT("expectedValue"),ExpectedValue);
  Out->SetStringField(TEXT("actualValueString"),C?C->GetString():TEXT("Missing"));
  if(C) Out->SetNumberField(TEXT("actualValue"),C->GetFloat());
  Out->SetNumberField(TEXT("actualPriority"),Priority); Out->SetNumberField(TEXT("expectedPriority"),ExpectedPriority);
  Out->SetStringField(TEXT("actualTag"),Tag.ToString()); Out->SetStringField(TEXT("expectedTag"),ExpectedTag.ToString());
  Out->SetBoolField(TEXT("verified"),bMatch);
 }
 if(!bMatch) Error=TEXT("CVar value, source priority or tag readback mismatch");
 return bMatch;
}
bool FURBCVarOverride::IsRestored() const {
 if(!bSnapshot) return true;
 auto* C=IConsoleManager::Get().FindConsoleVariable(*Name);
 return C && C->GetString()==OriginalValue && ((uint32)C->GetFlags()&(uint32)ECVF_SetByMask)==OriginalPriority && URBCurrentCVarTag(C)==OriginalTag;
}
bool FURBCVarOverride::Restore(TSharedPtr<FJsonObject> Out,FString& Error) {
 auto* C=IConsoleManager::Get().FindConsoleVariable(*Name);
 if(bSnapshot && bApplied && C) {
  if(bTemporary) C->Unset(ECVF_SetByTemp,TemporaryTag);
  else C->Set(*OriginalValue,IConsoleVariable::FResolvedContext{(EConsoleVariableFlags)OriginalPriority,OriginalTag});
  bApplied=false;
 }
 const bool bMatch=IsRestored();
 if(Out) {
  Describe(Out); Out->SetStringField(TEXT("actualValueString"),C?C->GetString():TEXT("Missing"));
  Out->SetNumberField(TEXT("actualPriority"),C?((uint32)C->GetFlags()&(uint32)ECVF_SetByMask):0);
  Out->SetStringField(TEXT("actualTag"),C?URBCurrentCVarTag(C).ToString():TEXT("Missing"));
  Out->SetBoolField(TEXT("restored"),bMatch);
 }
 if(!bMatch) Error=TEXT("CVar restoration value, source priority or tag mismatch");
 return bMatch;
}
void FURBCVarOverride::Describe(TSharedPtr<FJsonObject> Out) const {
 if(!Out) return;
 Out->SetStringField(TEXT("name"),Name); Out->SetStringField(TEXT("originalValue"),OriginalValue);
 Out->SetNumberField(TEXT("originalPriority"),OriginalPriority); Out->SetNumberField(TEXT("originalFlags"),OriginalFlags);
 Out->SetStringField(TEXT("originalTag"),OriginalTag.ToString());
 Out->SetStringField(TEXT("temporaryTag"),TemporaryTag.ToString());
 Out->SetStringField(TEXT("overrideMode"),bTemporary?TEXT("TemporaryTaggedOverride"):TEXT("ReplaceOriginalConsoleLayer"));
 Out->SetBoolField(TEXT("snapshotTaken"),bSnapshot);
}
