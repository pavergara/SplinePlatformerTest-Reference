using UnrealBuildTool;

public class BlueprintTextExporter : ModuleRules
{
	public BlueprintTextExporter(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[]
		{
			"Core",
			"CoreUObject",
			"Engine"
		});

		PrivateDependencyModuleNames.AddRange(new string[]
		{
			"UnrealEd",
			"AssetRegistry",
			"BlueprintGraph",
			"Kismet",
			"Slate",
			"SlateCore"
		});
	}
}
