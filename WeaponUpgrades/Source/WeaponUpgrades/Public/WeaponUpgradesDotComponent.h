// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FGDotComponent.h"

#include "WeaponUpgradesDotComponent.generated.h"

UCLASS(Blueprintable)
class WEAPONUPGRADES_API UWeaponUpgradesDotComponent : public UFGDotComponent
{
	GENERATED_BODY()

public:
	UWeaponUpgradesDotComponent();
	~UWeaponUpgradesDotComponent();
};
