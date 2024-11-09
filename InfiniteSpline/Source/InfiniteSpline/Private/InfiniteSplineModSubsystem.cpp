// Fill out your copyright notice in the Description page of Project Settings.


#include "InfiniteSplineModSubsystem.h"
#include <UnrealNetwork.h>

AInfiniteSplineModSubsystem::AInfiniteSplineModSubsystem()
{
}

AInfiniteSplineModSubsystem::~AInfiniteSplineModSubsystem()
{
}

void AInfiniteSplineModSubsystem::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AInfiniteSplineModSubsystem, RailMaxLength);
}

void AInfiniteSplineModSubsystem::BeginPlay()
{
	Super::BeginPlay();

}
