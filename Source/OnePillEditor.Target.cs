using UnrealBuildTool;
using System.Collections.Generic;

public class OnePillEditorTarget : TargetRules
{
	public OnePillEditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
		DefaultBuildSettings = BuildSettingsVersion.V5;
		IncludeOrderVersion = EngineIncludeOrderVersion.Latest;
		ExtraModuleNames.Add("OnePill");
	}
}
