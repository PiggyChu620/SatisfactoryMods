// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Module/GameInstanceModule.h"
#include "Resources/FGItemDescriptor.h"
#include "SatisFactorio.h"

#include "SatisFactorioGIM.generated.h"

/**
 * 
 */
UCLASS()
class SATISFACTORIO_API USatisFactorioGIM : public UGameInstanceModule
{
	GENERATED_BODY()
	
public:

	UPROPERTY(BlueprintReadWrite, Category = "SatisFactorio")
	TArray<TSubclassOf<UFGItemDescriptor>> AllFuels;

	UFUNCTION(BlueprintCallable, Category = "SatisFactorio")
	void GetAllFuels();

};
