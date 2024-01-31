// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"

DECLARE_LOG_CATEGORY_EXTERN(LogHiddenTreasures, Verbose, All);

class FHiddenTreasuresModule : public IModuleInterface
{
public:

	//UPROPERTY(BlueprintReadWrite, Category = "Hidden Treasures")
	//TArray<FItemDropWithChance> Items;

	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

};
