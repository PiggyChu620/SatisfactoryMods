// Fill out your copyright notice in the Description page of Project Settings.


#include "HiddenTreasuresBPFL.h"
#include "HiddenTreasures.h"
#include "Resources/FGItemDescriptor.h"
#include "Resources/FGResourceDescriptor.h"
#include "FGFoliageResourceUserData.h"

void UHiddenTreasuresBPFL::SetPickups(UStaticMesh* staticMesh, TMap< TSubclassOf<UFGItemDescriptor>, TSubclassOf<UFGItemDescriptor>> replacements)
{
	const TArray<UAssetUserData*>* ArrayPtr = staticMesh->GetAssetUserDataArray();
	if (ArrayPtr == nullptr) return;
	for (UAssetUserData* RawDatum : *ArrayPtr)
	{
		UFGFoliageResourceUserData* Datum = Cast<UFGFoliageResourceUserData>(RawDatum);
		if (Datum != NULL)
		{
			for (FItemDropWithChance& item : Datum->mPickupItems)
			{
				/*if (oldLeaves!=NULL && newLeaves!=NULL && item.Drop.ItemClass == oldLeaves)
				{
					item.Drop.ItemClass = newLeaves;
				}*/
				if (replacements.Contains(item.Drop.ItemClass)) item.Drop.ItemClass = replacements[item.Drop.ItemClass];
			}
		}
	}
}

void UHiddenTreasuresBPFL::AddPickups(TSet<UStaticMesh*> staticMeshes, TArray<FItemDropWithChance> items)
{
	for (UStaticMesh* staticMesh : staticMeshes)
	{
		UFGFoliageResourceUserData* data = staticMesh->GetAssetUserData<UFGFoliageResourceUserData>();

		for (FItemDropWithChance& item : items)
		{
			data->mPickupItems.Add(item);
		}
	}
	
}


