// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Module/GameWorldModule.h"
#include "Resources/FGItemDescriptor.h"
#include "SatisFactorio.h"

#include "SatisFactorioGWM.generated.h"

/**
 * 
 */
UCLASS()
class SATISFACTORIO_API USatisFactorioGWM : public UGameWorldModule
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, Category = "SatisFactorio")
	TArray<TSubclassOf<UFGItemDescriptor>> AllFuels;

	UFUNCTION(BlueprintCallable, Category = "SatisFactorio")
	void GetAllFuels();
};
