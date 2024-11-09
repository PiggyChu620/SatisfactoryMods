// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Resources/FGItemDescriptor.h"
#include "SatisFactorio.h"

/**
 * 
 */
class SATISFACTORIO_API FAssetLoadHandler
{
public:
	FAssetLoadHandler();
	~FAssetLoadHandler();

	TArray<TSubclassOf<UFGItemDescriptor>> AllFuels;
	void OnAssetLoaded(const FSoftObjectPath& Path);
};
