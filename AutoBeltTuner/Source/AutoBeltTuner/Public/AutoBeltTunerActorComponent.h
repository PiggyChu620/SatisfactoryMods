// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include <Components/ActorComponent.h>
#include <Net/UnrealNetwork.h>
#include "Buildables/FGBuildableConveyorBase.h"

#include "AutoBeltTunerActorComponent.generated.h"

UCLASS(BlueprintType)
class AUTOBELTTUNER_API UAutoBeltTunerActorComponent:public UActorComponent
{
	GENERATED_BODY()

public:
	UAutoBeltTunerActorComponent();
	~UAutoBeltTunerActorComponent();

	UPROPERTY(BlueprintReadWrite,Replicated, ReplicatedUsing = SetBeltSpeed, Category = "Auto Belt Tuner")
	float Speed;

	UFUNCTION(BlueprintCallable, Category = "Auto Belt Tuner")
	void SetBeltSpeed();

	UFUNCTION(Server,Reliable,WithValidation, Category = "Auto Belt Tuner")
	void SetBeltSpeed_Server(float newSpeed);
};
