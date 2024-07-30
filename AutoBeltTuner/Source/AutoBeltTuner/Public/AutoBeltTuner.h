// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"
#include "Module/GameInstanceModuleManager.h"
#include <EngineUtils.h>
#include "AutoBeltTuner.h"
#include "Subsystem/ModSubsystem.h"
#include "Subsystem/SubsystemActorManager.h"
#include "Patching/NativeHookManager.h"
#include "FGFactoryConnectionComponent.h"
#include "Buildables/FGBuildable.h"
#include "Buildables/FGBuildableFactory.h"
#include "Buildables/FGBuildableManufacturer.h"
#include "Buildables/FGBuildableConveyorBase.h"
#include "Buildables/FGBuildableConveyorBelt.h"
#include "Buildables/FGBuildableConveyorLift.h"
#include "FGRecipe.h"
#include "FGSaveInterface.h"
#include "AutoBeltTunerGameInstance.h"
#include "AutoBeltTunerActorComponent.h"

DECLARE_LOG_CATEGORY_EXTERN(LogAutoBeltTuner, Display, All);

class FAutoBeltTunerModule : public IModuleInterface
{
public:

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

	UFUNCTION(NetMulticast, Reliable, Category = "Auto Belt Tuner")
	static void hook(const bool& result, UFGFactoryConnectionComponent* self, FInventoryItem& out_item, float& out_OffsetBeyond, TSubclassOf< UFGItemDescriptor > type);
};
