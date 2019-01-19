// Copyright 2018-current Getnamo. All Rights Reserved


using System.IO;
using UnrealBuildTool;

namespace UnrealBuildTool.Rules
{
	public class SocketIO : ModuleRules
	{

	    private string ThirdPartyPath
	    {
	        get { return Path.GetFullPath(Path.Combine(ModuleDirectory, "../ThirdParty/")); }
	    }

	    private string SocketIOThirdParty
	    {
	        get { return Path.GetFullPath(Path.Combine(ThirdPartyPath, "SocketIO")); }
	    }

	    public bool LoadLib(ReadOnlyTargetRules Target)
	    {
	        bool isLibrarySupported = false;

	        if ((Target.Platform == UnrealTargetPlatform.Win64) || (Target.Platform == UnrealTargetPlatform.Win32))
	        {
	            isLibrarySupported = true;

	            /*string PlatformString = (Target.Platform == UnrealTargetPlatform.Win64) ? "Win64" : "Win32";
	            string BoostLibPath = Path.Combine(BoostThirdParty, "Lib");
	            string SocketLibPath = Path.Combine(SocketIOThirdParty, "Lib");

					
	            PublicAdditionalLibraries.Add(Path.Combine(SocketLibPath, PlatformString, "sioclient.lib"));
	            */
	        }

	        return isLibrarySupported;
	    }

	    public SocketIO(ReadOnlyTargetRules Target) : base(Target)
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
					Path.Combine(ModuleDirectory, "Private/lib/websocketpp"),
					Path.Combine(ModuleDirectory, "Private/lib/asio/asio/include"),
					Path.Combine(SocketIOThirdParty, "Include/lib/rapidjson/include"),
	                // ... add other private include paths required here ...
	            }
	            );


	        PublicDependencyModuleNames.AddRange(
	            new string[]
	            {
	            "Core",
				"CoreUtility"
	                // ... add other public dependencies that you statically link with here ...
	            }
	            );


	        PrivateDependencyModuleNames.AddRange(
	            new string[]
	            {
	            "CoreUObject",
	            "Engine",
	            "Slate",
	            "SlateCore",
	                // ... add private dependencies that you statically link with here ...	
	            }
	            );


	        DynamicallyLoadedModuleNames.AddRange(
	            new string[]
	            {
	                // ... add any modules that your module loads dynamically here ...
	            }
	            );

	        LoadLib(Target);
	    }
	}
}