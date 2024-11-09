// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystem/ModSubsystem.h"
#include "Resources/FGItemDescriptor.h"
#include "Algo/Transform.h"
#include "AssetRegistry/AssetRegistryModule.h"
#include "Engine/AssetManager.h"
#include "Engine/StreamableManager.h"
#include "SatisFactorio.h"
#include "FAssetLoadHandler.h"

#include "SatisFactorioSubsystem.generated.h"

/**
 * 
 */
UCLASS()
class SATISFACTORIO_API ASatisFactorioSubsystem : public AModSubsystem
{
	GENERATED_BODY()
	
public:
	ASatisFactorioSubsystem();
	~ASatisFactorioSubsystem();

	UFUNCTION(BlueprintCallable, Category = "SatisFactorio")
	TArray<TSubclassOf<UFGItemDescriptor>> GetAllFuels();

	TSharedPtr<FAssetLoadHandler> CallbackHandler;

protected:

	virtual void BeginPlay() override;
};
