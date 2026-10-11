// Copyright 2026-current Getnamo. All Rights Reserved

using UnrealBuildTool;

public class WebSocketClient : ModuleRules
{
	public WebSocketClient(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"Core",
				"CoreUObject",
				"Engine",
				"Json",
				"SIOJson",
			}
		);

		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
				"CoreUtility",
				"WebSocketLib",
			}
		);
	}
}
