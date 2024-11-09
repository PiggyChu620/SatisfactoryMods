// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"

#include "HiddenTreasuresGIM.h"

DECLARE_LOG_CATEGORY_EXTERN(LogHiddenTreasures, Display, All);

class FHiddenTreasuresModule : public IModuleInterface
{
public:

	//UPROPERTY(BlueprintReadWrite, Category = "Hidden Treasures")
	//TArray<FItemDropWithChance> Items;

	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

};
