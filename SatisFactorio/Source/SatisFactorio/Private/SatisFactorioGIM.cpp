// Fill out your copyright notice in the Description page of Project Settings.


#include "SatisFactorioGIM.h"


void USatisFactorioGIM::GetAllFuels()
{
    TArray<UClass*> nativeRootClasses;
    GetDerivedClasses(UFGItemDescriptor::StaticClass(), nativeRootClasses);
    nativeRootClasses.Add(UFGItemDescriptor::StaticClass());

    for (UClass* obj : nativeRootClasses)
    {
        if (IsValid(obj) && obj->HasAnyClassFlags(CLASS_Native))
        {
            UE_LOGFMT(LogSatisFactorio, Display, "Checking {0}", obj->GetName());
            UFGItemDescriptor* item = Cast<UFGItemDescriptor>(obj);
            if (IsValid(item) && UFGItemDescriptor::GetEnergyValue(item->GetClass()) > 0)
            {
                AllFuels.Emplace(item->GetClass());
                UE_LOGFMT(LogSatisFactorio, Display, "{0} added to the array", item->GetName());
            }
        }
    }
}
