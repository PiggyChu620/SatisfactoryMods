// Fill out your copyright notice in the Description page of Project Settings.


#include "FAssetLoadHandler.h"

FAssetLoadHandler::FAssetLoadHandler()
{
}

FAssetLoadHandler::~FAssetLoadHandler()
{
}

void FAssetLoadHandler::OnAssetLoaded(const FSoftObjectPath& Path)
{
    const TSubclassOf<UFGItemDescriptor> ItemClass = TSoftClassPtr<UFGItemDescriptor>(Path).Get();
    if (ItemClass)
    {
        UFGItemDescriptor* ItemCDO = ItemClass.GetDefaultObject();
        if (ItemCDO)
        {
            float energy = UFGItemDescriptor::GetEnergyValue(ItemClass);
            UE_LOGFMT(LogSatisFactorio, Display, "Energy Value of {0} is {1}",ItemCDO->GetName(), energy);
            if (energy > 0)
            {
                AllFuels.AddUnique(ItemClass);
                UE_LOGFMT(LogSatisFactorio, Display, "{0} is added to the fuel array", ItemCDO->GetName());
            }
        }
    }
    

}
