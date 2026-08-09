using UnrealBuildTool;
using System.Collections.Generic;

public class OnePillTarget : TargetRules
{
	public OnePillTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;
		DefaultBuildSettings = BuildSettingsVersion.V5;
		IncludeOrderVersion = EngineIncludeOrderVersion.Latest;
		ExtraModuleNames.Add("OnePill");
	}
}
