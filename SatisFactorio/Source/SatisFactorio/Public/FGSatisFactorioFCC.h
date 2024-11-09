// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FGFactoryConnectionComponent.h"
#include "SatisFactorio.h"

#include "FGSatisFactorioFCC.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class SATISFACTORIO_API UFGSatisFactorioFCC : public UFGFactoryConnectionComponent
{
	GENERATED_BODY()
	
public:
	bool Factory_PeekOutput(TArray< FInventoryItem >& out_items, TSubclassOf< class UFGItemDescriptor > type = nullptr) const;
};
