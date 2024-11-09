// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Module/GameInstanceModule.h"

#include <Engine/GameInstance.h>
#include <AssetRegistry/AssetRegistryModule.h>
#include "ItemDrop.h"
#include "FGInventoryComponent.h"
#include "Resources/FGItemDescriptor.h"
#include "Components/HierarchicalInstancedStaticMeshComponent.h"
#include "FGFoliageLibrary.h"
#include <NativeHookManager.h>

#include "HiddenTreasuresGIM.generated.h"

/**
 * 
 */
UCLASS()
class HIDDENTREASURES_API UHiddenTreasuresGIM : public UGameInstanceModule
{
	GENERATED_BODY()
	
public:
	UHiddenTreasuresGIM();
	~UHiddenTreasuresGIM();
	/*
	UPROPERTY(BlueprintReadWrite, Category = "Hidden Treasures")
	TArray<FItemDropWithChance> Items;

	UFUNCTION(BlueprintCallable, Category = "Hidden Treasures")
	void GetAllSinkableItems();
*/
	//UFUNCTION(NetMulticast, Reliable, Category = "Auto Belt Tuner")
	//void Hook(const bool& result, AFGCharacterPlayer* character, UHierarchicalInstancedStaticMeshComponent* meshComponent, TArrayView< uint32 > randomSeeds, TArray<struct FInventoryStack>& out_inventoryStacks);
};
