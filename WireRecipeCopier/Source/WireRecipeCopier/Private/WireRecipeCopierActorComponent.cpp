// Fill out your copyright notice in the Description page of Project Settings.


#include "WireRecipeCopierActorComponent.h"

UWireRecipeCopierActorComponent::UWireRecipeCopierActorComponent()
{
	SetIsReplicatedByDefault(true);
}

UWireRecipeCopierActorComponent::~UWireRecipeCopierActorComponent()
{
}


//void UWireRecipeCopierActorComponent::PasteSettings()
//{
//	AFGBuildableFactory* factory = Cast<AFGBuildableFactory>(GetOwner());
//
//	factory->Execute_PasteSettings(factory, Settings);
//}
//
//void UWireRecipeCopierActorComponent::PasteSettings_Server_Implementation(UFGFactoryClipboardSettings* newSettings)
//{
//	Settings = newSettings;
//	PasteSettings();
//}
//
//bool UWireRecipeCopierActorComponent::PasteSettings_Server_Validate(UFGFactoryClipboardSettings* newSettings)
//{
//	return true;
//}

void UWireRecipeCopierActorComponent::SetPotential()
{
	AFGBuildableFactory* factory = Cast<AFGBuildableFactory>(GetOwner());
	//UE_LOG(LogWireRecipeCopier, Display, TEXT("Player Inventory: %s"),*GetPlayerInventory()->GetName());
	int shardsNeeded = FMath::CeilToInt((Potential - 1.0) * 2.0);
	if (shardsNeeded > 0)
	{
		int shardsHave = GetPowerShardAmount();
		UE_LOG(LogWireRecipeCopier, Display, TEXT("Shards Have: %d"), shardsHave);
		int shardsTaken = shardsHave > shardsNeeded ? shardsNeeded : shardsHave;
		int n = factory->GetPotentialInventory()->AddStack(FInventoryStack(shardsTaken, PowerShard),true);
		if (n > 0) GetPlayerInventory()->Remove(PowerShard, n);
	}
	factory->SetPendingPotential(Potential);
}

void UWireRecipeCopierActorComponent::SetPotential_Server_Implementation(float newPotential)
{
	Potential = newPotential;
	SetPotential();
}

bool UWireRecipeCopierActorComponent::SetPotential_Server_Validate(float newPotential)
{
	return true;
}

void UWireRecipeCopierActorComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UWireRecipeCopierActorComponent, Potential);
	DOREPLIFETIME(UWireRecipeCopierActorComponent, PowerShard);
}