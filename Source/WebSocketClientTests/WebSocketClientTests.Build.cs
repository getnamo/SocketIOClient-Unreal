// Copyright 2026-current Getnamo. All Rights Reserved

using System.IO;
using UnrealBuildTool;

public class WebSocketClientTests : ModuleRules
{
	private string ThirdPartyPath
	{
		get { return Path.GetFullPath(Path.Combine(ModuleDirectory, "../ThirdParty/")); }
	}

	public WebSocketClientTests(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		//The in-process test server uses websocketpp/asio like WebSocketLib
		bUseRTTI = true;
		bEnableExceptions = true;

		PrivateIncludePaths.AddRange(
			new string[] {
				Path.Combine(ThirdPartyPath, "websocketpp"),
				Path.Combine(ThirdPartyPath, "asio/asio/include"),
			}
		);

		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
				"Core",
				"CoreUObject",
				"Engine",
				"Json",
				"OpenSSL",
				"SIOJson",
				"WebSocketLib",
				"WebSocketClient",
			}
		);

		if (
			(Target.Version.MajorVersion == 5 && Target.Version.MinorVersion >= 3) ||
			Target.Version.MajorVersion > 5
		)
		{
			PrivateDefinitions.Add("ASIO_HAS_STD_INVOKE_RESULT=1");
		}
	}
}
