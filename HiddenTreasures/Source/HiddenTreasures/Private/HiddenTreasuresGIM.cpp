// Fill out your copyright notice in the Description page of Project Settings.


#include "HiddenTreasuresGIM.h"

UHiddenTreasuresGIM::UHiddenTreasuresGIM()
{/*
    if (!WITH_EDITOR)
    {
        SUBSCRIBE_METHOD_AFTER(UFGFoliageLibrary::CheckInventorySpaceAndGetStacks, [&](const bool& result, AFGCharacterPlayer* character, UHierarchicalInstancedStaticMeshComponent* meshComponent, TArrayView<uint32> randomSeeds, TArray<struct FInventoryStack>& out_inventoryStacks){
            for (FItemDropWithChance& item : Items)
            {
                if (IsValid(item.Drop.ItemClass) && FMath::RandRange(0.0, 1.0) <= item.DropChance)
                {
                    //UE_LOG(LogHiddenTreasures, Verbose, TEXT("%s"), *item.Drop.ItemClass->GetPathName());
                    out_inventoryStacks.Emplace(FInventoryStack(FMath::RandRange(item.Drop.NumItems.Min, item.Drop.NumItems.Max), item.Drop.ItemClass));
                }
            }
        });
    }*/
}

UHiddenTreasuresGIM::~UHiddenTreasuresGIM()
{
}


/*
void UHiddenTreasuresGIM::Hook
{
    //if (IsValid(world))
    //{
        //AHiddenTreasuresModSubsystem* subsystem = AHiddenTreasuresModSubsystem::Get(world);
        //UHiddenTreasuresGIM* gim = Cast<UHiddenTreasuresGIM>(character->GetGameInstance()->GetSubsystem<UGameInstanceModuleManager>()->FindModule(FName("HiddenTreasures")));
        //if (IsValid(subsystem))
        //{
        
        //}
    //}
}
*/