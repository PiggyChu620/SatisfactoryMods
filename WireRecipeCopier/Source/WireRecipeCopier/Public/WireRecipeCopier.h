// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"
#include "WireRecipeCopierActorComponent.h"
#include "WRCPlayerStateComponent.h"
#include "RecipeCopierWireModSubsystem.h"
#include "WireRecipeCopierGIM.h"
#include "FGPlayerController.h"
#include "FGPlayerState.h"
#include "GameFramework/GameStateBase.h"
#include <Logging/StructuredLog.h>

DECLARE_LOG_CATEGORY_EXTERN(LogWireRecipeCopier, Display, All);

class FWireRecipeCopierModule : public IModuleInterface
{
public:

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

	static void hook(const AActor* result, AFGWireHologram* self, TArray< AActor* >& out_children, FNetConstructionID netConstructionID);

};
