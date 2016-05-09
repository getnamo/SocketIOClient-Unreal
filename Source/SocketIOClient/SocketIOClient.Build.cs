// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

using System.IO;

namespace UnrealBuildTool.Rules
{
    public class SocketIOClient : ModuleRules
    {
        private string ThirdPartyPath
        {
            get { return Path.GetFullPath(Path.Combine(ModuleDirectory, "../../ThirdParty/")); }
        }

        private string SocketIOThirdParty
        {
            get { return Path.GetFullPath(Path.Combine(ThirdPartyPath, "SocketIO")); }
        }
        private string BoostThirdParty
        {
            get { return Path.GetFullPath(Path.Combine(ThirdPartyPath, "Boost")); }
        }

        public bool LoadLib(TargetInfo Target)
        {
            bool isLibrarySupported = false;

            if ((Target.Platform == UnrealTargetPlatform.Win64) || (Target.Platform == UnrealTargetPlatform.Win32))
            {
                isLibrarySupported = true;

                string PlatformString = (Target.Platform == UnrealTargetPlatform.Win64) ? "Win64" : "Win32";
                string BoostLibPath = Path.Combine(BoostThirdParty, "Lib");
                string SocketLibPath = Path.Combine(SocketIOThirdParty, "Lib");

                PublicAdditionalLibraries.Add(Path.Combine(BoostLibPath, PlatformString, "libboost_date_time-vc140-mt-1_60.lib"));
                PublicAdditionalLibraries.Add(Path.Combine(BoostLibPath, PlatformString, "libboost_random-vc140-mt-1_60.lib"));
                PublicAdditionalLibraries.Add(Path.Combine(BoostLibPath, PlatformString, "libboost_system-vc140-mt-1_60.lib"));
                PublicAdditionalLibraries.Add(Path.Combine(SocketLibPath, PlatformString, "sioclient.lib"));
                
            }
            return isLibrarySupported;
        }

        public SocketIOClient(TargetInfo Target)
        {

            PublicIncludePaths.AddRange(
                new string[] {
                "SocketIOClient/Public",
                    Path.Combine(BoostThirdParty, "Include"),
                    Path.Combine(SocketIOThirdParty, "Include"),
                    // ... add public include paths required here ...
                }
                );


            PrivateIncludePaths.AddRange(
                new string[] {
                "SocketIOClient/Private",
                
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