// Copyright 2018-current Getnamo. All Rights Reserved


using UnrealBuildTool;

public class CoreUtility : ModuleRules
{
    public CoreUtility(ReadOnlyTargetRules Target) : base(Target)
    {
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicIncludePaths.AddRange(
            new string[] {
                "CoreUtility/Public"
            }
            );


        PrivateIncludePaths.AddRange(
            new string[] {
                "CoreUtility/Private",
            }
            );


        PublicDependencyModuleNames.AddRange(
            new string[]
            {
                "Core"
            }
            );


        PrivateDependencyModuleNames.AddRange(
            new string[]
            {
                "CoreUObject",
                "Engine",
				"RHI",
				"RenderCore"
			}
            );


        DynamicallyLoadedModuleNames.AddRange(
            new string[]
            {
            }
            );
    }
}