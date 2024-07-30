// Fill out your copyright notice in the Description page of Project Settings.


#include "AutoBeltTunerActorComponent.h"

UAutoBeltTunerActorComponent::UAutoBeltTunerActorComponent()
{
	SetIsReplicatedByDefault(true);
}

UAutoBeltTunerActorComponent::~UAutoBeltTunerActorComponent()
{
}

void UAutoBeltTunerActorComponent::SetBeltSpeed()
{
	AFGBuildableConveyorBase* belt = Cast<AFGBuildableConveyorBase>(GetOwner());

	if(IsValid(belt)) belt->mSpeed = Speed;
}

void UAutoBeltTunerActorComponent::SetBeltSpeed_Server_Implementation(float newSpeed)
{
	Speed = newSpeed;
	SetBeltSpeed();
}

bool UAutoBeltTunerActorComponent::SetBeltSpeed_Server_Validate(float newSpeed)
{
	return true;
}

void UAutoBeltTunerActorComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UAutoBeltTunerActorComponent, Speed);
}
