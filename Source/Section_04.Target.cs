// Copyright 2017 Red Rabbit Games, Inc.

using UnrealBuildTool;
using System.Collections.Generic;

public class Section_04Target : TargetRules
{
	public Section_04Target(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;

		ExtraModuleNames.AddRange( new string[] { "Section_04" } );
	}
}
