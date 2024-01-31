// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include <CoreMinimal.h>
#include <Kismet/BlueprintFunctionLibrary.h>
#include "Subsystem/ModSubsystem.h"
#include "ItemDrop.h"
#include "FGInventoryComponent.h"
#include "Patching/NativeHookManager.h"
#include "FGFoliageLibrary.h"
#include "FGFoliageResourceUserData.h"
#include "HiddenTreasures.h"

#include "AHiddenTreasuresModSubsystem.generated.h"

UCLASS(Abstract)
class HIDDENTREASURES_API AHiddenTreasuresModSubsystem : public AModSubsystem
{
	GENERATED_BODY()

public:
	AHiddenTreasuresModSubsystem();
	~AHiddenTreasuresModSubsystem();

	UPROPERTY(BlueprintReadWrite, Category = "Hidden Treasures")
	TArray<FItemDropWithChance> Items;

	UFUNCTION(BlueprintImplementableEvent, Category = "Hidden Treasures")
	void SpawnCrateWith(int32 Stacks);

protected:
	virtual void BeginPlay() override;
};
