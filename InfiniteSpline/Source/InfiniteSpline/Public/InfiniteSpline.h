// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"
#include "Patching/NativeHookManager.h"
#include "Hologram/FGConveyorBeltHologram.h"
#include "Hologram/FGPipelineHologram.h"
#include "Hologram/FGWireHologram.h"
#include "Hologram/FGRailroadTrackHologram.h"
#include "Hologram/FGConveyorLiftHologram.h"
#include "Buildables/FGBuildableConveyorBelt.h"
#include "Buildables/FGBuildablePipeline.h"
#include "Buildables/FGBuildableWire.h"
#include "Buildables/FGBuildableRailroadTrack.h"
#include "Buildables/FGBuildableConveyorLift.h"
#include "Buildables/FGBuildableConveyorAttachment.h"
#include "Buildables/FGBuildableAttachmentSplitter.h"
#include "Buildables/FGBuildableAttachmentMerger.h"
#include "Buildables/FGBuildableSplitterSmart.h"
#include "Buildables/FGBuildableBlueprintDesigner.h"
#include "InfiniteSplineModSubsystem.h"
#include "FGConstructDisqualifier.h"
#include <EngineUtils.h>
#include <StructuredLog.h>
#include "Algo/Sort.h"
#include "FGBlueprintSubsystem.h"


DECLARE_LOG_CATEGORY_EXTERN(LogInfiniteSpline, Display, All);

class FInfiniteSplineModule : public IModuleInterface
{
public:

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

private:
	static void splitHook(const TArray<AFGBuildableConveyorBelt*>& result,  AFGBuildableConveyorBelt* conveyor, float offset, bool connectNewConveyors);
	static void attachmentHook(AFGBuildableConveyorAttachment* self);
};
