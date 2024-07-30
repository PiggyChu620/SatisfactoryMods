// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystem/ModSubsystem.h"
#include "Hologram/FGConveyorBeltHologram.h"
#include "Patching/NativeHookManager.h"

#include "InfiniteSplineModSubsystem.generated.h"
/**
 * 
 */
UCLASS(Abstract)
class INFINITESPLINE_API AInfiniteSplineModSubsystem : public AModSubsystem
{
	GENERATED_BODY()

public:
	AInfiniteSplineModSubsystem();
	~AInfiniteSplineModSubsystem();

protected:
	virtual void BeginPlay() override;
};
