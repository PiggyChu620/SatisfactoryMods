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

	SUBSCRIBE_METHOD(UFGFoliageLibrary::GetValidInventoryStacks, [&](auto& scope, UFGFoliageResourceUserData* foliageUserData, uint32 randomSeed)
		{
			TArray<FInventoryStack> theStacks = scope(foliageUserData, randomSeed);
			for (FItemDropWithChance& item : Items)
			{
				if (IsValid(item.Drop.ItemClass) && FMath::RandRange(0.0, 1.0) <= item.DropChance)
				{
					//UE_LOG(LogHiddenTreasures, Verbose, TEXT("%s"), *item.Drop.ItemClass->GetPathName());
					theStacks.Emplace(FInventoryStack(FMath::RandRange(item.Drop.NumItems.Min, item.Drop.NumItems.Max), item.Drop.ItemClass));
				}
			}
			//for (int i=0;i< foliageUserData->mPickupItems.Num();i++)
			//{
			//	FItemDropWithChance& item = foliageUserData->mPickupItems[i];
			//	if (IsValid(item.Drop.ItemClass) && FMath::RandRange(0.0, 1.0) <= item.DropChance)
			//	{
			//		//UE_LOG(LogHiddenTreasures, Verbose, TEXT("%d: %s"), i,*item.Drop.ItemClass->GetPathName());
			//		theStacks.Emplace(FInventoryStack(FMath::RandRange(item.Drop.NumItems.Min, item.Drop.NumItems.Max), item.Drop.ItemClass));
			//	}
			//}
			scope.Override(theStacks);
			//
		});
}
