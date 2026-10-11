// Copyright 2026-current Getnamo. All Rights Reserved

using System.IO;
using UnrealBuildTool;

public class WebSocketLib : ModuleRules
{
	private string ThirdPartyPath
	{
		get { return Path.GetFullPath(Path.Combine(ModuleDirectory, "../ThirdParty/")); }
	}

	public WebSocketLib(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		//websocketpp and asio need these, they stay private to this module
		bUseRTTI = true;
		bEnableExceptions = true;

		PrivateIncludePaths.AddRange(
			new string[] {
				Path.Combine(ThirdPartyPath, "websocketpp"),
				Path.Combine(ThirdPartyPath, "asio/asio/include"),
			}
		);

		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"Core",
			}
		);

		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
				"OpenSSL",
				"SSL",
			}
		);

		//Same as SocketIOLib, both modules have to compile the shared websocketpp/asio headers identically
		if (
			(Target.Version.MajorVersion == 5 && Target.Version.MinorVersion >= 3) ||
			Target.Version.MajorVersion > 5
		)
		{
			PrivateDefinitions.Add("ASIO_HAS_STD_INVOKE_RESULT=1");
		}
	}
}
