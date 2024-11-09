// Fill out your copyright notice in the Description page of Project Settings.


#include "FGSatisFactorioFCC.h"

bool UFGSatisFactorioFCC::Factory_PeekOutput(TArray<FInventoryItem>& out_items, TSubclassOf<class UFGItemDescriptor> type) const
{
	UE_LOGFMT(LogSatisFactorio, Display, "Checking PeekOutput...");
	bool result = UFGFactoryConnectionComponent::Factory_PeekOutput(out_items, type);

	return result;
}
