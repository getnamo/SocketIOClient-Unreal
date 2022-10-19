// Copyright 2018-current Getnamo. All Rights Reserved


using System.IO;
using UnrealBuildTool;

namespace UnrealBuildTool.Rules
{
	public class SocketIOLib : ModuleRules
	{
		private string ThirdPartyPath
		{
			get { return Path.GetFullPath(Path.Combine(ModuleDirectory, "../ThirdParty/")); }
		}

			public SocketIOLib(ReadOnlyTargetRules Target) : base(Target)
			{
				PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
				bUseRTTI = true;
				bEnableExceptions = true;

				PublicIncludePaths.AddRange(
					new string[] {
						Path.Combine(ModuleDirectory, "Public"),
					}
				);


				PrivateIncludePaths.AddRange(
					new string[] {
						Path.Combine(ModuleDirectory, "Private"),
						Path.Combine(ModuleDirectory, "Private/internal"),
						Path.Combine(ThirdPartyPath, "websocketpp"),
						Path.Combine(ThirdPartyPath, "asio/asio/include"),
						Path.Combine(ThirdPartyPath, "rapidjson/include"),
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
						"CoreUObject",
						"Engine",
						"OpenSSL"
					}
				);


				DynamicallyLoadedModuleNames.AddRange(
					new string[]
					{
					}
				);

				//Setup TLS support | Maybe other platforms work as well (untested)
				if (
					Target.Platform == UnrealTargetPlatform.Win64 ||
					Target.Platform == UnrealTargetPlatform.Mac ||
					Target.Platform == UnrealTargetPlatform.Linux ||
					Target.Platform == UnrealTargetPlatform.IOS||
					Target.Platform == UnrealTargetPlatform.Android
				)
				{
					PublicDefinitions.Add("SIO_TLS=1");
				}
			}
	}
}
