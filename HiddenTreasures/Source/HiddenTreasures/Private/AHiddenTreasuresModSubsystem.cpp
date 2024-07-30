// Fill out your copyright notice in the Description page of Project Settings.

#include "AHiddenTreasuresModSubsystem.h"
#include "HiddenTreasures.h"

//DEFINE_LOG_CATEGORY(LogHiddenTreasures);

AHiddenTreasuresModSubsystem::AHiddenTreasuresModSubsystem()
{
	
}

AHiddenTreasuresModSubsystem::~AHiddenTreasuresModSubsystem()
{
}

void AHiddenTreasuresModSubsystem::BeginPlay()
{
	Super::BeginPlay();

	for (FItemDropWithChance& item : Items)
	{
		UFGItemDescriptor* cdo = Cast< UFGItemDescriptor>(item.Drop.ItemClass->GetClass()->ClassDefaultObject);
		if (IsValid(cdo) && cdo->mResourceSinkPoints != 0)
		{
			float c = item.DropChance;
			item.DropChance = .001f / (float)cdo->mResourceSinkPoints;
			UE_LOG(LogHiddenTreasures, Display, TEXT("Change drop chance of %s from %f to %f"), *cdo->mDisplayName.ToString(),c, item.DropChance);
		}
	}
	//SUBSCRIBE_METHOD(UFGFoliageLibrary::GetValidInventoryStacks, [](auto& scope, UFGFoliageResourceUserData* foliageUserData, uint32 randomSeed)
	//	{
	//		TArray<FInventoryStack> theStacks = scope(foliageUserData, randomSeed);
	//		UWorld* world = foliageUserData->GetWorld();

	//		//if (IsValid(world))
	//		//{
	//			AHiddenTreasuresModSubsystem* subsystem = AHiddenTreasuresModSubsystem::Get(world);

	//			//if (IsValid(subsystem))
	//			//{
	//				for (FItemDropWithChance& item : subsystem->Items)
	//				{
	//					if (IsValid(item.Drop.ItemClass) && FMath::RandRange(0.0, 1.0) <= item.DropChance)
	//					{
	//						//UE_LOG(LogHiddenTreasures, Verbose, TEXT("%s"), *item.Drop.ItemClass->GetPathName());
	//						theStacks.Emplace(FInventoryStack(FMath::RandRange(item.Drop.NumItems.Min, item.Drop.NumItems.Max), item.Drop.ItemClass));
	//					}
	//				}
	//				//for (int i=0;i< foliageUserData->mPickupItems.Num();i++)
	//				//{
	//				//	FItemDropWithChance& item = foliageUserData->mPickupItems[i];
	//				//	if (IsValid(item.Drop.ItemClass) && FMath::RandRange(0.0, 1.0) <= item.DropChance)
	//				//	{
	//				//		//UE_LOG(LogHiddenTreasures, Verbose, TEXT("%d: %s"), i,*item.Drop.ItemClass->GetPathName());
	//				//		theStacks.Emplace(FInventoryStack(FMath::RandRange(item.Drop.NumItems.Min, item.Drop.NumItems.Max), item.Drop.ItemClass));
	//				//	}
	//				//}
	//			//}
	//			
	//		//}
	//		
	//		scope.Override(theStacks);
	//	});

	//SUBSCRIBE_METHOD(UFGFoliageLibrary::HasPlayerInventorySpaceFor, [](auto& scope, AFGCharacterPlayer* character, UHierarchicalInstancedStaticMeshComponent* meshComponent, uint32 randomSeed)
	//	{
	//		UE_LOG(LogHiddenTreasures, Display, TEXT("HasPlayerInventorySpaceFor Called"));
	//		meshComponent->AssetUserData()
	//	});

	SUBSCRIBE_METHOD_AFTER(UFGFoliageLibrary::CheckInventorySpaceAndGetStacks, [](const bool& result, AFGCharacterPlayer* character, UHierarchicalInstancedStaticMeshComponent* meshComponent, TArrayView< uint32 > randomSeeds, TArray<struct FInventoryStack>& out_inventoryStacks)
		{
			/*for (FInventoryStack i : out_inventoryStacks)
			{
				UE_LOG(LogHiddenTreasures, Display, TEXT("Item: %s, Amount: %d"), *i.Item.GetItemClass()->GetName(), i.NumItems);
			}*/
			UWorld* world = character->GetWorld();
			if (IsValid(world))
			{
				AHiddenTreasuresModSubsystem* subsystem = AHiddenTreasuresModSubsystem::Get(world);
				if (IsValid(subsystem))
				{
					for (FItemDropWithChance& item : subsystem->Items)
					{
						if (IsValid(item.Drop.ItemClass) && FMath::RandRange(0.0, 1.0) <= item.DropChance)
						{
							//UE_LOG(LogHiddenTreasures, Verbose, TEXT("%s"), *item.Drop.ItemClass->GetPathName());
							out_inventoryStacks.Emplace(FInventoryStack(FMath::RandRange(item.Drop.NumItems.Min, item.Drop.NumItems.Max), item.Drop.ItemClass));
						}
					}
				}
			}
		});

	/*SUBSCRIBE_METHOD(UFGFoliageLibrary::TryAddToPlayerInventory, [](auto& scope, AFGCharacterPlayer* character, UHierarchicalInstancedStaticMeshComponent* meshComponent, uint32 randomSeed)
		{
			UE_LOG(LogHiddenTreasures, Display, TEXT("HasPlayerInventorySpaceFor Called"));
		});*/
}
