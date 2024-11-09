// Fill out your copyright notice in the Description page of Project Settings.


#include "SatisFactorioGWM.h"
#include <Registry/ModContentRegistry.h>

void USatisFactorioGWM::GetAllFuels()
{
	if (AllFuels.IsEmpty())
	{
		UE_LOGFMT(LogSatisFactorio, Display, "Running GetAllFuels()");
		/*for(TObjectIterator<UFGItemDescriptor> It; It; ++It)
		{
			UFGItemDescriptor* item = *It;
			UE_LOGFMT(LogSatisFactorio, Display, "Checking {0}", item->GetName());
			if (item && UFGItemDescriptor::GetEnergyValue(item->GetClass()) > 0)
			{
				AllFuels.AddUnique(item->GetClass());
				UE_LOGFMT(LogSatisFactorio, Display, "{0} added to the array", item->GetName());
			}
		}*/
		TArray<UObject*> items;
		GetObjectsOfClass(UFGItemDescriptor::StaticClass(),items,true,EObjectFlags::RF_BeginDestroyed);
		for (UObject* i : items) 
		{
			UE_LOGFMT(LogSatisFactorio, Display, "Checking {0}", i->GetName());
			UFGItemDescriptor* item = Cast<UFGItemDescriptor>(i);

			if(IsValid(item) && UFGItemDescriptor::GetEnergyValue(item->GetClass()) > 0)
			{
				AllFuels.AddUnique(item->GetClass());
				UE_LOGFMT(LogSatisFactorio, Display, "{0} added to the array", item->GetName());
			}
		}
		
	}
}
