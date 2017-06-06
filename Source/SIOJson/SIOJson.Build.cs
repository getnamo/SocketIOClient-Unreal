// Copyright 2014 Vladimir Alyamkin. All Rights Reserved.

using System.IO;

namespace UnrealBuildTool.Rules
{
	public class SIOJson : ModuleRules
	{
		public SIOJson(ReadOnlyTargetRules Target) : base(Target)
        {
			PrivateIncludePaths.AddRange(
				new string[] {
					"SIOJson/Private",
					// ... add other private include paths required here ...
				});

			PublicDependencyModuleNames.AddRange(
				new string[]
				{
					"Core",
					"CoreUObject",
					"Engine",
                    "HTTP",
                    "Json",
                    "JsonUtilities"
					// ... add other public dependencies that you statically link with here ...
				});
		}
	}
}