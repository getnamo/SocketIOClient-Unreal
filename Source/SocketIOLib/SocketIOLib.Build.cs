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
					Path.Combine(ThirdPartyPath, "openssl/x64/include")
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
	            }
	            );


	        DynamicallyLoadedModuleNames.AddRange(
	            new string[]
	            {
	            }
	            );


			if (Target.Platform == UnrealTargetPlatform.Win64)
			{ // setup TLS support 

				PublicDefinitions.Add("SIO_TLS");

				if (Target.Type == TargetType.Editor)
				{
					PublicAdditionalLibraries.Add(Path.Combine(ThirdPartyPath, "openssl/x64/lib/libcrypto.lib"));
					PublicAdditionalLibraries.Add(Path.Combine(ThirdPartyPath, "openssl/x64/lib/libssl.lib"));
				}
				RuntimeDependencies.Add(Path.Combine(ThirdPartyPath, "openssl/x64/bin/libcrypto-1_1-x64.dll"));
				RuntimeDependencies.Add(Path.Combine(ThirdPartyPath, "openssl/x64/bin/libssl-1_1-x64.dll"));

				RuntimeDependencies.Add(Path.Combine(PluginDirectory, "Binaries/Win64/libcrypto-1_1-x64.dll"),
					Path.Combine(ThirdPartyPath, "openssl/x64/bin/libcrypto-1_1-x64.dll"));
				RuntimeDependencies.Add(Path.Combine(PluginDirectory, "Binaries/Win64/libssl-1_1-x64.dll"),
					Path.Combine(ThirdPartyPath, "openssl/x64/bin//libssl-1_1-x64.dll"));

				RuntimeDependencies.Add("$(TargetOutputDir)/libcrypto-1_1-x64.dll",
					Path.Combine(ThirdPartyPath, "openssl/x64/bin/libcrypto-1_1-x64.dll"));
				RuntimeDependencies.Add("$(TargetOutputDir)/libssl-1_1-x64.dll", 
					Path.Combine(ThirdPartyPath, "openssl/x64/bin/libssl-1_1-x64.dll"));

			}
		}
	}
}