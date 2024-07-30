// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include <Engine/GameInstance.h>
#include <AssetRegistry/AssetRegistryModule.h>
#include "AutoBeltTunerModSubsystem.h"
#include "Buildables/FGBuildableConveyorBase.h"
#include "Buildables/FGBuildableConveyorBelt.h"
#include "Buildables/FGBuildableConveyorLift.h"
#include "Patching/BlueprintSCSHookManager.h"
#include "AutoBeltTunerActorComponent.h"

#include "AutoBeltTunerGameInstance.generated.h"

UCLASS()
class AUTOBELTTUNER_API UAutoBeltTunerGameInstanceModule : public UGameInstanceModule
{
	GENERATED_BODY()

public:
	UAutoBeltTunerGameInstanceModule();
	~UAutoBeltTunerGameInstanceModule();

	UPROPERTY(BlueprintReadWrite, SaveGame, Category = "Auto Belt Tuner")
	AAutoBeltTunerModSubsystem* Subsystem;
	
	UFUNCTION(BlueprintCallable, Category = "Auto Belt Tuner")
	void HookAllBelts(UBlueprintSCSHookManager* manager, TArray<TSoftClassPtr<AActor>> Belts);
};
