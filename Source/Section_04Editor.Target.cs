// Copyright 2017 Red Rabbit Games, Inc.

using UnrealBuildTool;
using System.Collections.Generic;

public class Section_04EditorTarget : TargetRules
{
	public Section_04EditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;

		ExtraModuleNames.AddRange( new string[] { "Section_04" } );
	}
}
