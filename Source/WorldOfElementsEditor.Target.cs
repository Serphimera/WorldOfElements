// Copyright 2015 Nethersoft (Sebastian Kenter). All rights reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class WorldOfElementsEditorTarget : TargetRules
{
	public WorldOfElementsEditorTarget(TargetInfo Target)
	{
		Type = TargetType.Editor;
	}

	//
	// TargetRules interface.
	//

	public override void SetupBinaries(
		TargetInfo Target,
		ref List<UEBuildBinaryConfiguration> OutBuildBinaryConfigurations,
		ref List<string> OutExtraModuleNames
		)
	{
		OutExtraModuleNames.AddRange( new string[] { "WorldOfElements" } );
	}
}
