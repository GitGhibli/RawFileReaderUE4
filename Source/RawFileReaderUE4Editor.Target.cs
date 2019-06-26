// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;
using System.Collections.Generic;

public class RawFileReaderUE4EditorTarget : TargetRules
{
	public RawFileReaderUE4EditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;

		ExtraModuleNames.AddRange( new string[] { "RawFileReaderUE4" } );
	}
}
