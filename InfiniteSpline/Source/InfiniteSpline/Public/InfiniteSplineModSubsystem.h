// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystem/ModSubsystem.h"
#include "Hologram/FGConveyorBeltHologram.h"
#include "Patching/NativeHookManager.h"
#include "FGBlueprintSubsystem.h"
#include <EngineUtils.h>

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

	UPROPERTY(BlueprintReadWrite,SaveGame,Replicated, Category = "Infinite Spline")
	float RailMaxLength;

	UPROPERTY(BlueprintReadWrite, SaveGame, Replicated, Category = "Infinite Spline")
	float RailMaxClimb=25.0;

	UPROPERTY(BlueprintReadWrite, SaveGame, Replicated, Category = "Infinite Spline")
	float RailMinBend=15.0;

	UPROPERTY(BlueprintReadWrite, SaveGame, Replicated, Category = "Infinite Spline")
	bool RailEnabled=true;

	UPROPERTY(BlueprintReadWrite, SaveGame, Replicated, Category = "Infinite Spline")
	bool WireEnabled=true;

	UPROPERTY(BlueprintReadWrite, SaveGame, Replicated, Category = "Infinite Spline")
	bool BeltEnabled=true;

	UPROPERTY(BlueprintReadWrite, SaveGame, Replicated, Category = "Infinite Spline")
	bool PipeEnabled=true;

	UPROPERTY(BlueprintReadWrite, SaveGame, Replicated, Category = "Infinite Spline")
	bool HypertubeEnabled=true;

	UFUNCTION(BlueprintImplementableEvent, Category = "Infinite Spline")
	void InGamePrint(const FString& text);

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	static AInfiniteSplineModSubsystem* Get(UWorld* world)
	{
		/*for (TActorIterator<AModSubsystem> It(world, AModSubsystem::StaticClass(), EActorIteratorFlags::AllActors); It; ++It)
		{
			AModSubsystem* CurrentActor = *It;
		}
		for (TActorIterator<AInfiniteSplineModSubsystem> It(world, AInfiniteSplineModSubsystem::StaticClass(), EActorIteratorFlags::AllActors); It; ++It) {
			AInfiniteSplineModSubsystem* CurrentActor = *It;
		}*/
		for (TActorIterator<AInfiniteSplineModSubsystem> It(world, AInfiniteSplineModSubsystem::StaticClass(), EActorIteratorFlags::AllActors); It; ++It) {
			AInfiniteSplineModSubsystem* CurrentActor = *It;
			if (CurrentActor) {
				return CurrentActor;
			}
		}
		return NULL;
	}

protected:
	virtual void BeginPlay() override;
};
