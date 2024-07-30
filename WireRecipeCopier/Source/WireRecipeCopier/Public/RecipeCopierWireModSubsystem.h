// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include <EngineUtils.h>
#include "WireRecipeCopier.h"
#include "Subsystem/ModSubsystem.h"
#include "FGRecipeManager.h"
#include "Patching/NativeHookManager.h"
#include "Hologram/FGHologram.h"
#include "Hologram/FGWireHologram.h"
#include "Buildables/FGBuildableFactory.h"
#include "Buildables/FGBuildableManufacturer.h"
#include "FGCharacterPlayer.h"

#include "RecipeCopierWireModSubsystem.generated.h"

UCLASS(Abstract)
class WIRERECIPECOPIER_API ARecipeCopierWireModSubsystem : public AModSubsystem
{
	GENERATED_BODY()

public:
	ARecipeCopierWireModSubsystem();
	~ARecipeCopierWireModSubsystem();

	

	/*UFUNCTION(BlueprintImplementableEvent, Category = "Recipe Copier Wire")
	bool GetIfShiftHold();*/


	UFUNCTION(BlueprintImplementableEvent, Category = "Recipe Copier Wire")
	UFGManufacturerClipboardRCO* GetClipboardRCO();

	UFUNCTION(BlueprintImplementableEvent, Category = "Recipe Copier Wire")
	void InGamePrint(const FString& str);


	/*UPROPERTY(BlueprintReadWrite,Replicated, Category = "Recipe Copier Wire")
	bool IsCtrlHold;*/

	

	/*UFUNCTION(NetMulticast, Reliable, Category = "Recipe Copier Wire")
	void CopyRecipe();*/

	/*UFUNCTION(BlueprintCallable, Category = "Recipe Copier Wire")
	void Init(AFGRecipeManager* RecipeManager,TSubclassOf<UFGRecipe> recipe);*/

	TMap<FString,UFGManufacturerClipboardSettings*> CopiedSettings;
	TMap<FString, float> Potentials;

	static ARecipeCopierWireModSubsystem* Get(UWorld* world)
	{
		for (TActorIterator<ARecipeCopierWireModSubsystem> It(world, ARecipeCopierWireModSubsystem::StaticClass(), EActorIteratorFlags::AllActors); It; ++It)
		{
			ARecipeCopierWireModSubsystem* CurrentActor = *It;
			if (CurrentActor)
			{
				return CurrentActor;
			}
		}
		return NULL;
	}

protected:
	virtual void BeginPlay() override;

};
