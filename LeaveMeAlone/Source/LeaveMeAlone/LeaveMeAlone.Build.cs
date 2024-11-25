// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;

public class LeaveMeAlone : ModuleRules
{
	public LeaveMeAlone(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
        // PublicIncludePaths.Add(Path.Combine(ModuleDirectory,  "D:\Games2024\Task\Ta_3\LeaveMeAlone\Source\LeaveMeAlone" ));
        PublicIncludePaths.AddRange(new string[] { "LeaveMeAlone" });
        PublicIncludePaths.AddRange(new string[] { "D:\\Games2024\\Task\\Ta_3\\LeaveMeAlone\\Source\\LeaveMeAlone" });// … add public include paths required here …
		PublicIncludePaths.AddRange(new string[] { "D:\\Games2024\\Task\\Ta_3\\LeaveMeAlone" });
        PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore" });

		PrivateDependencyModuleNames.AddRange(new string[] {  });
	}
}
