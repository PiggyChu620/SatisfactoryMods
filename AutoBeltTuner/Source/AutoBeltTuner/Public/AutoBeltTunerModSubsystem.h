// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include <EngineUtils.h>
#include "AutoBeltTuner.h"
#include "Subsystem/ModSubsystem.h"
#include "Subsystem/SubsystemActorManager.h"
#include "Patching/NativeHookManager.h"
#include "FGFactoryConnectionComponent.h"
#include "Buildables/FGBuildable.h"
#include "Buildables/FGBuildableFactory.h"
#include "Buildables/FGBuildableManufacturer.h"
#include "Buildables/FGBuildableConveyorBase.h"
#include "FGRecipe.h"
#include "FGSaveInterface.h"
#include "Module/GameInstanceModuleManager.h"
#include "HAL/CriticalSection.h"
#include "HAL/RunnableThread.h"
#include <Misc/ScopeTryLock.h>

#include "AutoBeltTunerModSubsystem.generated.h"

UCLASS(Abstract)
class AUTOBELTTUNER_API AAutoBeltTunerModSubsystem : public AModSubsystem
{
	GENERATED_BODY()

public:
	AAutoBeltTunerModSubsystem();
	~AAutoBeltTunerModSubsystem();

	/*UPROPERTY(BlueprintReadWrite, Category = "Auto Belt Tuner")
	TMap<FString,float> BeltSpeeds;

	UFUNCTION(BlueprintImplementableEvent, Category = "Auto Belt Tuner")
	float GetBeltSpeed(AFGBuildableConveyorBase* belt);*/

	UFUNCTION(NetMulticast, Reliable, Category = "Auto Belt Tuner")
	void SetBeltSpeed(AFGBuildableConveyorBase* belt, float speed);

	/*TMap<AFGBuildableConveyorBase*,TSharedPtr<TMpscQueue<float>>> speedQueues;
	bool running=false;*/
	//UPROPERTY(Replicated, Category = "Auto Belt Tuner")
	FCriticalSection CriticalSection;

protected:
	virtual void BeginPlay() override;
//	virtual void Tick(float ds) override;
	
};
