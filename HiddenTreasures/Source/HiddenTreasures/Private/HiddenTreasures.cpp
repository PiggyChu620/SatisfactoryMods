// Copyright Epic Games, Inc. All Rights Reserved.

#include "HiddenTreasures.h"
#include "Patching/NativeHookManager.h"
#include "FGFoliageLibrary.h"
#include "FGFoliageResourceUserData.h"
#include "FGInventoryComponent.h"
#include "Math/UnrealMathUtility.h"
#include "AHiddenTreasuresModSubsystem.h"
#include <Kismet/GameplayStatics.h>

#define LOCTEXT_NAMESPACE "FHiddenTreasuresModule"

DEFINE_LOG_CATEGORY(LogHiddenTreasures);


void FHiddenTreasuresModule::StartupModule()
{
	//SUBSCRIBE_METHOD(UFGFoliageLibrary::GetValidInventoryStacks, [&](auto& scope, UFGFoliageResourceUserData* foliageUserData, uint32 randomSeed)
	//	{
	//		TArray<FInventoryStack> theStacks = scope(foliageUserData, randomSeed);
	//		for (FItemDropWithChance& item : Items)
	//		{
	//			if (IsValid(item.Drop.ItemClass) && FMath::RandRange(0.0, 1.0) <= item.DropChance)
	//			{
	//				theStacks.Emplace(FInventoryStack(FMath::RandRange(item.Drop.NumItems.Min, item.Drop.NumItems.Max), item.Drop.ItemClass));
	//			}
	//		}
	//		//for (int i=0;i< foliageUserData->mPickupItems.Num();i++)
	//		//{
	//		//	FItemDropWithChance& item = foliageUserData->mPickupItems[i];
	//		//	if (IsValid(item.Drop.ItemClass) && FMath::RandRange(0.0, 1.0) <= item.DropChance)
	//		//	{
	//		//		//UE_LOG(LogHiddenTreasures, Verbose, TEXT("%d: %s"), i,*item.Drop.ItemClass->GetPathName());
	//		//		theStacks.Emplace(FInventoryStack(FMath::RandRange(item.Drop.NumItems.Min, item.Drop.NumItems.Max), item.Drop.ItemClass));
	//		//	}
	//		//}
	//		//scope.Override(theStacks);
	//		//
	//	});
}

void FHiddenTreasuresModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
}


#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FHiddenTreasuresModule, HiddenTreasures)