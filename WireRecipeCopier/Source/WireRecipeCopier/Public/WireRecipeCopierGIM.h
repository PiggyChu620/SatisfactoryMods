// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include <Engine/GameInstance.h>
#include <AssetRegistry/AssetRegistryModule.h>
#include <Patching/BlueprintSCSHookManager.h>
#include "RecipeCopierWireModSubsystem.h"
#include "Module/GameInstanceModuleManager.h"

#include "WireRecipeCopierGIM.generated.h"

UCLASS()
class WIRERECIPECOPIER_API UWireRecipeCopierGIM : public UGameInstanceModule
{
	GENERATED_BODY()

public:
	UWireRecipeCopierGIM();
	~UWireRecipeCopierGIM();

	UPROPERTY(BlueprintReadWrite, SaveGame, Category = "Wire Recipe Copier")
	ARecipeCopierWireModSubsystem* Subsystem;

	UFUNCTION(BlueprintCallable, Category = "Wire Recipe Copier")
	void HookAllFactories(UBlueprintSCSHookManager* manager, TSubclassOf<UWireRecipeCopierActorComponent> component);
};
