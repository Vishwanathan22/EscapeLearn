// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class EscapeLearn : ModuleRules
{
	public EscapeLearn(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] {
			"Core",
			"CoreUObject",
			"Engine",
			"InputCore",
			"EnhancedInput",
			"AIModule",
			"StateTreeModule",
			"GameplayStateTreeModule",
			"UMG",
			"Slate"
		});

		PrivateDependencyModuleNames.AddRange(new string[] { });

		PublicIncludePaths.AddRange(new string[] {
			"EscapeLearn",
			"EscapeLearn/Variant_Horror",
			"EscapeLearn/Variant_Horror/UI",
			"EscapeLearn/Variant_Shooter",
			"EscapeLearn/Variant_Shooter/AI",
			"EscapeLearn/Variant_Shooter/UI",
			"EscapeLearn/Variant_Shooter/Weapons"
		});

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
