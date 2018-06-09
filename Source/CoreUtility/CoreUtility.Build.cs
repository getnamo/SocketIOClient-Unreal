// Copyright 2018-current Getnamo. All Rights Reserved
// Available under MIT license at https://github.com/getnamo/socketio-client-ue4

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
            }
            );


        DynamicallyLoadedModuleNames.AddRange(
            new string[]
            {
            }
            );
    }
}