// Copyright 2018-current Getnamo. All Rights Reserved


using System.IO;

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

            if ((Target.Platform == UnrealTargetPlatform.Win64) || (Target.Platform == UnrealTargetPlatform.Win32))
            {
                isLibrarySupported = true;

                string PlatformString = (Target.Platform == UnrealTargetPlatform.Win64) ? "Win64" : "Win32";
                string BoostLibPath = Path.Combine(BoostThirdParty, "Lib");
                string SocketLibPath = Path.Combine(SocketIOThirdParty, "Lib");
				if (Target.Platform == UnrealTargetPlatform.Win32)
				{
					PublicAdditionalLibraries.Add(Path.Combine(BoostLibPath, PlatformString, "libboost_date_time-vc141-mt-x32-1_66.lib"));
					PublicAdditionalLibraries.Add(Path.Combine(BoostLibPath, PlatformString, "libboost_random-vc141-mt-x32-1_66.lib"));
					PublicAdditionalLibraries.Add(Path.Combine(BoostLibPath, PlatformString, "libboost_system-vc141-mt-x32-1_66.lib"));
				}
				else
				{
					PublicAdditionalLibraries.Add(Path.Combine(BoostLibPath, PlatformString, "libboost_date_time-vc141-mt-x64-1_66.lib"));
					PublicAdditionalLibraries.Add(Path.Combine(BoostLibPath, PlatformString, "libboost_random-vc141-mt-x64-1_66.lib"));
					PublicAdditionalLibraries.Add(Path.Combine(BoostLibPath, PlatformString, "libboost_system-vc141-mt-x64-1_66.lib"));
				}

					
                PublicAdditionalLibraries.Add(Path.Combine(SocketLibPath, PlatformString, "sioclient.lib"));

            }
            else if (Target.Platform == UnrealTargetPlatform.Linux)
            {
                isLibrarySupported = true;

                string PlatformString = "Linux";
                string BoostLibPath = Path.Combine(BoostThirdParty, "Lib");
                string SocketLibPath = Path.Combine(SocketIOThirdParty, "Lib");

                PublicAdditionalLibraries.Add(Path.Combine(BoostLibPath, PlatformString, "libboost_date_time-clang39-mt-1_60.a"));
                PublicAdditionalLibraries.Add(Path.Combine(BoostLibPath, PlatformString, "libboost_random-clang39-mt-1_60.a"));
                PublicAdditionalLibraries.Add(Path.Combine(BoostLibPath, PlatformString, "libboost_system-clang39-mt-1_60.a"));
                PublicAdditionalLibraries.Add(Path.Combine(SocketLibPath, PlatformString, "libsioclient.a"));
            }
            else if (Target.Platform == UnrealTargetPlatform.IOS)
            {
                isLibrarySupported = true;

                string PlatformString = "IOS";
                string BoostLibPath = Path.Combine(BoostThirdParty, "Lib");
                string SocketLibPath = Path.Combine(SocketIOThirdParty, "Lib");

                PublicAdditionalLibraries.Add(Path.Combine(BoostLibPath, PlatformString, "libboost_date_time.a"));
                PublicAdditionalLibraries.Add(Path.Combine(BoostLibPath, PlatformString, "libboost_random.a"));
                PublicAdditionalLibraries.Add(Path.Combine(BoostLibPath, PlatformString, "libboost_system.a"));
                PublicAdditionalLibraries.Add(Path.Combine(SocketLibPath, PlatformString, "libsioclient.a"));
            }
            else if (Target.Platform == UnrealTargetPlatform.Mac)
            {
                isLibrarySupported = true;

                string PlatformString = "Mac";
                string BoostLibPath = Path.Combine(BoostThirdParty, "Lib");
                string SocketLibPath = Path.Combine(SocketIOThirdParty, "Lib");

                PublicAdditionalLibraries.Add(Path.Combine(BoostLibPath, PlatformString, "libboost_date_time.a"));
                PublicAdditionalLibraries.Add(Path.Combine(BoostLibPath, PlatformString, "libboost_random.a"));
                PublicAdditionalLibraries.Add(Path.Combine(BoostLibPath, PlatformString, "libboost_system.a"));
                PublicAdditionalLibraries.Add(Path.Combine(SocketLibPath, PlatformString, "libsioclient.a"));
            }
            else if (Target.Platform == UnrealTargetPlatform.Android)
            {
                isLibrarySupported = true;

                string PlatformString = "Android";
				//string AndroidPlatform = "arm64-v8a";   
				string AndroidPlatform = "armeabi-v7a"; //change to armeabi-v7a if using 32bit
				string BoostLibPath = Path.Combine(BoostThirdParty, "Lib");
                string SocketLibPath = Path.Combine(SocketIOThirdParty, "Lib");

                PublicAdditionalLibraries.Add(Path.Combine(BoostLibPath, PlatformString, AndroidPlatform, "libboost_date_time.a"));
                PublicAdditionalLibraries.Add(Path.Combine(BoostLibPath, PlatformString, AndroidPlatform, "libboost_random.a"));
                PublicAdditionalLibraries.Add(Path.Combine(BoostLibPath, PlatformString, AndroidPlatform, "libboost_system.a"));
                PublicAdditionalLibraries.Add(Path.Combine(SocketLibPath, PlatformString, AndroidPlatform, "libsioclient.a"));
            }

            return isLibrarySupported;
        }

        public SocketIOClient(ReadOnlyTargetRules Target) : base(Target)
        {
			PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

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
                "Json",
                "JsonUtilities",
                "SIOJson",
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