// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System.IO;

public class Blade : ModuleRules
{
	public Blade(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] {
			"Core",
			"CoreUObject",
			"Engine",
			"InputCore"
		});

		PrivateDependencyModuleNames.AddRange(new string[] {
			"UMG",
			"GameplayAbilities",
			"GameplayTags",
			"GameplayTasks"
		});

		PublicIncludePaths.AddRange(new string[] {
			Path.Combine("Blade", "Public/Abilities"),
			Path.Combine("Blade", "Public/Animations"),
			Path.Combine("Blade", "Public/AI"),
			Path.Combine("Blade", "Public/Widgets")
		});
	}
}
