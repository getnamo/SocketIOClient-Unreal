// Copyright 2018-current Getnamo. All Rights Reserved


using System.IO;
using UnrealBuildTool;

namespace UnrealBuildTool.Rules
{
    public class SocketIOClient : ModuleRules
    {

        private string ThirdPartyPath
        {
            get { return Path.GetFullPath(Path.Combine(ModuleDirectory, "../ThirdParty/")); }
        }

        private string SocketIOThirdParty
        {
            get { return Path.GetFullPath(Path.Combine(ThirdPartyPath, "SocketIO")); }
        }
        private string BoostThirdParty
        {
            get { return Path.GetFullPath(Path.Combine(ThirdPartyPath, "Boost")); }
        }

        public bool LoadLib(ReadOnlyTargetRules Target)
        {
            bool isLibrarySupported = false;

            if (Target.Platform == UnrealTargetPlatform.Win64)
            {
                isLibrarySupported = true;
            }
            else if (Target.Platform == UnrealTargetPlatform.Linux)
            {
                isLibrarySupported = true;
            }
            else if (Target.Platform == UnrealTargetPlatform.IOS)
            {
                isLibrarySupported = true;
            }
            else if (Target.Platform == UnrealTargetPlatform.Mac)
            {
                isLibrarySupported = true;
            }
            else if (Target.Platform == UnrealTargetPlatform.Android)
            {
                isLibrarySupported = true;
            }

            return isLibrarySupported;
        }

        public SocketIOClient(ReadOnlyTargetRules Target) : base(Target)
        {
			PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

			PublicIncludePaths.AddRange(
                new string[] {
					Path.Combine(ModuleDirectory, "Public"),
                    // ... add public include paths required here ...
                }
                );


            PrivateIncludePaths.AddRange(
                new string[] {
					Path.Combine(ModuleDirectory, "Private"),
                    // ... add other private include paths required here ...
                }
                );


            PublicDependencyModuleNames.AddRange(
                new string[]
                {
                "Core",
                "Json",
                "JsonUtilities",
                "SIOJson",
				"CoreUtility",
                "SocketIOLib",
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