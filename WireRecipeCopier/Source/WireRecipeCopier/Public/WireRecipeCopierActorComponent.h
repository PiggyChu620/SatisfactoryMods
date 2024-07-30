// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include <Components/ActorComponent.h>
#include <Net/UnrealNetwork.h>
#include "Buildables/FGBuildableFactory.h"
#include "Buildables/FGBuildableManufacturer.h"
#include "RecipeCopierWireModSubsystem.h"
#include "FGCharacterPlayer.h"
#include "FGInventoryComponent.h"

#include "WireRecipeCopierActorComponent.generated.h"

UCLASS(Blueprintable)
class WIRERECIPECOPIER_API UWireRecipeCopierActorComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UWireRecipeCopierActorComponent();
	~UWireRecipeCopierActorComponent();

	UPROPERTY(BlueprintReadWrite, Replicated, ReplicatedUsing = SetPotential, Category = "Wire Recipe Copier")
	float Potential;

	//UPROPERTY(BlueprintReadWrite, Replicated, ReplicatedUsing = PasteSettings, Category = "Wire Recipe Copier")
	//UFGFactoryClipboardSettings* Settings;

	UFUNCTION(BlueprintCallable, Category = "Wire Recipe Copier")
	void SetPotential();

	UFUNCTION(Server, Reliable, WithValidation, Category = "Wire Recipe Copier")
	void SetPotential_Server(float newPotential);

	//UFUNCTION(BlueprintCallable, Category = "Wire Recipe Copier")
	//void PasteSettings();

	//UFUNCTION(Server, Reliable, WithValidation, Category = "Wire Recipe Copier")
	//void PasteSettings_Server(UFGFactoryClipboardSettings* newSettings);

	ARecipeCopierWireModSubsystem* Subsystem;

	UFUNCTION(BlueprintImplementableEvent, Category = "Recipe Copier Wire")
	int GetPowerShardAmount();

	UFUNCTION(BlueprintImplementableEvent, Category = "Recipe Copier Wire")
	UFGInventoryComponent* GetPlayerInventory();

	UPROPERTY(BlueprintReadWrite, Replicated, Category = "Recipe Copier Wire")
	TSubclassOf<UFGItemDescriptor> PowerShard;
};
