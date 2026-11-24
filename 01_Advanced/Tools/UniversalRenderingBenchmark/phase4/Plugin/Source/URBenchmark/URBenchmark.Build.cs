using UnrealBuildTool;
public class URBenchmark : ModuleRules {
  public URBenchmark(ReadOnlyTargetRules Target) : base(Target) {
    PCHUsage=PCHUsageMode.UseExplicitOrSharedPCHs;
    PublicDependencyModuleNames.AddRange(new string[]{"Core","CoreUObject","Engine","InputCore"});
    PrivateDependencyModuleNames.AddRange(new string[]{"Json","RenderCore","RHI","Projects"});
    if(Target.Platform==UnrealTargetPlatform.Win64) PublicSystemLibraries.Add("bcrypt.lib");
  }
}
