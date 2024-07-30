// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WireRecipeCopier.h"
#include "Hologram/FGWireHologram.h"

#include "FGRecipeCopierWireHologram.generated.h"

UCLASS()
class AFGRecipeCopierWireHologram : public AFGWireHologram
{
	GENERATED_BODY()

public:
	AFGRecipeCopierWireHologram();
	~AFGRecipeCopierWireHologram();

	//virtual void ConfigureActor(class AFGBuildable* inBuildable) const override;
};
