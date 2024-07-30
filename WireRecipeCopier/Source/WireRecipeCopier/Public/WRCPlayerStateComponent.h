// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include <Components/ActorComponent.h>
#include <Net/UnrealNetwork.h>
#include "Buildables/FGBuildableFactory.h"
#include "Buildables/FGBuildableManufacturer.h"
#include "WireRecipeCopierActorComponent.h"

#include "WRCPlayerStateComponent.generated.h"

UCLASS(Blueprintable)
class WIRERECIPECOPIER_API UWRCPlayerStateComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UWRCPlayerStateComponent();
	~UWRCPlayerStateComponent();

	UPROPERTY(BlueprintReadWrite,Replicated, Category = "Wire Recipe Copier | WRCPlayerStateComponent")
	bool IsCtrlHold;

	UFUNCTION(BlueprintCallable,Server, Reliable, WithValidation, Category = "Wire Recipe Copier | WRCPlayerStateComponent")
	void SetCtrl_Server(bool isHold);

	TMap<FString, UFGManufacturerClipboardSettings*> CopiedSettings;
	TMap<FString, float> CopiedPotentials;

	UFUNCTION(BlueprintImplementableEvent, Category = "Wire Recipe Copier | WRCPlayerStateComponent")
	void InGamePrint(const FString& str);

	void CopySettings(AFGBuildableManufacturer* manufacturer);
	void PasteSettings(AFGBuildableManufacturer* manufacturer, FString& newManufacturerName);

	void CopyPotential(AFGBuildableFactory* factory);
	void PastePotential(AFGBuildableFactory* factory, FString& newFactoryName);
};
