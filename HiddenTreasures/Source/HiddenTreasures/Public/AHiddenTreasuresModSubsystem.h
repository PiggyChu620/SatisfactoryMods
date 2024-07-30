// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include <CoreMinimal.h>
#include <Kismet/BlueprintFunctionLibrary.h>
#include <EngineUtils.h>
#include "Subsystem/ModSubsystem.h"
#include "ItemDrop.h"
#include "FGInventoryComponent.h"
#include "Patching/NativeHookManager.h"
#include "FGFoliageLibrary.h"
#include "FGFoliageResourceUserData.h"
#include "HiddenTreasures.h"
#include "FGCharacterPlayer.h"

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

	static AHiddenTreasuresModSubsystem* Get(UWorld* world)
	{
		for (TActorIterator<AModSubsystem> It(world, AModSubsystem::StaticClass(), EActorIteratorFlags::AllActors); It; ++It)
		{
			AModSubsystem* CurrentActor = *It;
		}
		for (TActorIterator<AHiddenTreasuresModSubsystem> It(world, AHiddenTreasuresModSubsystem::StaticClass(), EActorIteratorFlags::AllActors); It; ++It) {
			AHiddenTreasuresModSubsystem* CurrentActor = *It;
		}
		/* End log spam */
		for (TActorIterator<AHiddenTreasuresModSubsystem> It(world, AHiddenTreasuresModSubsystem::StaticClass(), EActorIteratorFlags::AllActors); It; ++It) {
			AHiddenTreasuresModSubsystem* CurrentActor = *It;
			if (CurrentActor) {
				return CurrentActor;
			}
		}
		return NULL;
	}

protected:
	virtual void BeginPlay() override;
};
