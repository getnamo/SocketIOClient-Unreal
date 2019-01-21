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
	                // ... add public include paths required here ...
	            }
	            );


	        PrivateIncludePaths.AddRange(
	            new string[] {
					Path.Combine(ModuleDirectory, "Private"),
					Path.Combine(ModuleDirectory, "Private/internal"),
					Path.Combine(ThirdPartyPath, "websocketpp"),
					Path.Combine(ThirdPartyPath, "asio"),
					Path.Combine(ThirdPartyPath, "rapidjson"),
	                // ... add other private include paths required here ...
	            }
	            );


	        PublicDependencyModuleNames.AddRange(
	            new string[]
	            {
	            "Core",
	                // ... add other public dependencies that you statically link with here ...
	            }
	            );


	        PrivateDependencyModuleNames.AddRange(
	            new string[]
	            {
	            "CoreUObject",
	            "Engine",
	                // ... add private dependencies that you statically link with here ...	
	            }
	            );


	        DynamicallyLoadedModuleNames.AddRange(
	            new string[]
	            {
	                // ... add any modules that your module loads dynamically here ...
	            }
	            );
	    }
	}
}