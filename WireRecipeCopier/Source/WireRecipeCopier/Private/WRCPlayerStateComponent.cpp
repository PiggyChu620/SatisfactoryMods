// Fill out your copyright notice in the Description page of Project Settings.


#include "WRCPlayerStateComponent.h"

UWRCPlayerStateComponent::UWRCPlayerStateComponent()
{
	//SetIsReplicatedByDefault(true);
}

UWRCPlayerStateComponent::~UWRCPlayerStateComponent()
{
}

void UWRCPlayerStateComponent::CopySettings(AFGBuildableManufacturer* manufacturer)
{
	CopiedSettings.FindOrAdd(manufacturer->mDisplayName.ToString()) = Cast<UFGManufacturerClipboardSettings>(manufacturer->Execute_CopySettings(manufacturer));
}

void UWRCPlayerStateComponent::PasteSettings(AFGBuildableManufacturer* manufacturer, FString& newManufacturerName)
{
	if (CopiedSettings.Contains(newManufacturerName))
	{
		manufacturer->Execute_PasteSettings(manufacturer, CopiedSettings[newManufacturerName]);
	}
}

void UWRCPlayerStateComponent::CopyPotential(AFGBuildableFactory* factory)
{
	CopiedPotentials.FindOrAdd(factory->mDisplayName.ToString()) = factory->GetCurrentPotential();
}

void UWRCPlayerStateComponent::PastePotential(AFGBuildableFactory* factory, FString& newFactoryName)
{
	if (CopiedPotentials.Contains(newFactoryName))
	{
		TArray<UWireRecipeCopierActorComponent*> components;
		
		factory->GetComponents(components,true);
		if (components.Num()>0)
		{
			components[0]->SetPotential_Server(CopiedPotentials[newFactoryName]);
		}
	}
}

void UWRCPlayerStateComponent::SetCtrl_Server_Implementation(bool isHold)
{
	IsCtrlHold = isHold;
}

bool UWRCPlayerStateComponent::SetCtrl_Server_Validate(bool isHold)
{
	return true;
}

void UWRCPlayerStateComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UWRCPlayerStateComponent, IsCtrlHold);
}