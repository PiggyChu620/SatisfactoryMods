// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include <CoreMinimal.h>
#include <Kismet/BlueprintFunctionLibrary.h>
#include "Resources/FGItemDescriptor.h"
#include "Resources/FGResourceDescriptor.h"
#include "FGFoliageResourceUserData.h"

#include "HiddenTreasuresBPFL.generated.h"

UCLASS()
class HIDDENTREASURES_API UHiddenTreasuresBPFL : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()


	UFUNCTION(BlueprintCallable, Category = "Hidden Treasures BPFL")
	static void SetPickups(UStaticMesh* staticMesh, TMap< TSubclassOf<UFGItemDescriptor>, TSubclassOf<UFGItemDescriptor>> replacements);

	UFUNCTION(BlueprintCallable, Category = "Hidden Treasures BPFL")
	static void AddPickups(TSet<UStaticMesh*> staticMesh, TArray<FItemDropWithChance> items);

};
