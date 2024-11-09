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
#include "FGResourceSinkSettings.h"
#include "FGCategory.h"
#include "FGEventSubsystem.h"
#include "FGResourceSinkSubsystem.h"
#include "Resources/FGEquipmentDescriptor.h"

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

	/*UPROPERTY(BlueprintReadWrite, Category = "Hidden Treasures")
	UDataTable* SinkPoints;*/

	UPROPERTY(BlueprintReadWrite, SaveGame, Category = "Hidden Treasures")
	double DropChance;

	UPROPERTY(BlueprintReadWrite, SaveGame, Category = "Hidden Treasures")
	double EqupmentMultiplier=1.0;

	UPROPERTY(BlueprintReadWrite, SaveGame, Category = "Hidden Treasures")
	int32 MinSinkPoint = 20;

	UPROPERTY(BlueprintReadWrite, Category = "Hidden Treasures")
	AFGEventSubsystem* EventSubsystem;

	UPROPERTY(BlueprintReadWrite, Category = "Hidden Treasures")
	AFGResourceSinkSubsystem* ResourceSinkSubsystem;

	UPROPERTY(BlueprintReadWrite, Category = "Hidden Treasures")
	TSubclassOf<UFGCategory> FICSMAS;

	UPROPERTY(BlueprintReadWrite, Category = "Hidden Treasures")
	TArray<TSubclassOf<UFGItemDescriptor>> BannedItems;

	UFUNCTION(BlueprintCallable, Category = "Hidden Treasures")
	void GetAllSinkableItems();

	UFUNCTION(BlueprintImplementableEvent, Category = "Hidden Treasures")
	void InGamePrint(const FString& text);

	//int32 Count = 0;
	TMap<TSubclassOf<UFGItemDescriptor>, int> ItemPoints;
	bool IsFicsmas;
	//UFUNCTION(BlueprintImplementableEvent, Category = "Hidden Treasures")
	//void SpawnCrateWith(int32 Stacks);

	static AHiddenTreasuresModSubsystem* Get(UWorld* world)
	{
		for (TActorIterator<AModSubsystem> It(world, AModSubsystem::StaticClass(), EActorIteratorFlags::AllActors); It; ++It)
		{
			AModSubsystem* CurrentActor = *It;
		}
		for (TActorIterator<AHiddenTreasuresModSubsystem> It(world, AHiddenTreasuresModSubsystem::StaticClass(), EActorIteratorFlags::AllActors); It; ++It) {
			AHiddenTreasuresModSubsystem* CurrentActor = *It;
		}
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

private:
};
