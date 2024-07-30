// Copyright Epic Games, Inc. All Rights Reserved.

#include "InfiniteSpline.h"

#define LOCTEXT_NAMESPACE "FInfiniteSplineModule"

void FInfiniteSplineModule::StartupModule()
{
	if (not WITH_EDITOR)
	{
		AFGConveyorBeltHologram* beltHologram = GetMutableDefault<AFGConveyorBeltHologram>();
		SUBSCRIBE_METHOD_VIRTUAL_AFTER(AFGConveyorBeltHologram::BeginPlay, beltHologram, [](AFGConveyorBeltHologram* self)
			{
				if (IsValid(self))
				{
					self->mMaxSplineLength = 1000000000000.0;
				}
			});
		
		AFGPipelineHologram* pipeHologram = GetMutableDefault<AFGPipelineHologram>();
		SUBSCRIBE_METHOD_VIRTUAL_AFTER(AFGPipelineHologram::BeginPlay, pipeHologram, [](AFGPipelineHologram* self)
			{
				if (IsValid(self))
				{
					self->mMaxSplineLength = 1000000000000.0;
				}
			});

		AFGWireHologram* wireHologram = GetMutableDefault<AFGWireHologram>();
		SUBSCRIBE_METHOD_VIRTUAL_AFTER(AFGWireHologram::BeginPlay, wireHologram, [](AFGWireHologram* self)
			{
				if (IsValid(self))
				{
					self->mMaxLength = 1000000000000.0;
					self->mMaxPowerTowerLength = 1000000000000.0;
				}
			});

		AFGRailroadTrackHologram* railHologram = GetMutableDefault<AFGRailroadTrackHologram>();
		SUBSCRIBE_METHOD_VIRTUAL_AFTER(AFGRailroadTrackHologram::BeginPlay, railHologram, [](AFGRailroadTrackHologram* self)
			{
				if (IsValid(self))
				{
					self->mMaxLength = 1000000000000.0;
				}
			});

		AFGConveyorLiftHologram* liftHologram = GetMutableDefault<AFGConveyorLiftHologram>();
		SUBSCRIBE_METHOD_VIRTUAL_AFTER(AFGConveyorLiftHologram::BeginPlay, liftHologram, [](AFGConveyorLiftHologram* self)
			{
				if (IsValid(self))
				{
					self->mMaximumHeight = 1000000000000.0;
				}
			});
	}
}

void FInfiniteSplineModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FInfiniteSplineModule, InfiniteSpline)