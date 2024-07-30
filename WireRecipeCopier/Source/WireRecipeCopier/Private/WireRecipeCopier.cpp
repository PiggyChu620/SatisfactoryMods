// Copyright Epic Games, Inc. All Rights Reserved.

#include "WireRecipeCopier.h"

#define LOCTEXT_NAMESPACE "FWireRecipeCopierModule"

DEFINE_LOG_CATEGORY(LogWireRecipeCopier);

void FWireRecipeCopierModule::StartupModule()
{
	if (not WITH_EDITOR)
	{
		AFGWireHologram* hologram = GetMutableDefault<AFGWireHologram>();
		SUBSCRIBE_METHOD_VIRTUAL_AFTER(AFGWireHologram::Construct, hologram, &hook);
	}
}

void FWireRecipeCopierModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
}

void FWireRecipeCopierModule::hook(const AActor* result, AFGWireHologram* self, TArray<AActor*>& out_children, FNetConstructionID netConstructionID)
{
	//UE_LOG(LogWireRecipeCopier, Display, TEXT("Hook calling..."));
	if (IsValid(result))
	{
		const AFGBuildableWire* wire = Cast<AFGBuildableWire>(result);
		if (IsValid(wire))
		{
			//ARecipeCopierWireModSubsystem* subsystem = ARecipeCopierWireModSubsystem::Get(wire->GetWorld());
			//UWireRecipeCopierGIM* module = Cast<UWireRecipeCopierGIM>(wire->GetGameInstance()->GetSubsystem<UGameInstanceModuleManager>()->FindModule(FName("WireRecipeCopier")));
			//module->Subsystem->InGamePrint(TEXT("GIM Acquired"));
			//UE_LOG(LogWireRecipeCopier, Display, TEXT("GIM Acquired"));
			UWRCPlayerStateComponent* playerComponent=nullptr;
			AFGPlayerController* playerController=nullptr;
			AGameStateBase* gameState = UGameplayStatics::GetGameState(wire->GetWorld());
			for (APlayerState* playerState : gameState->PlayerArray)
			{
				APlayerController* aPlayerController = playerState->GetPlayerController();
				if (IsValid(aPlayerController))
				{
					playerController = Cast<AFGPlayerController>(aPlayerController);
					playerComponent = playerState->GetComponentByClass<UWRCPlayerStateComponent>();
					if (IsValid(playerComponent)) break;
				}
			}
			if (IsValid(playerComponent))
			{
				//UE_LOG(LogWireRecipeCopier, Display, TEXT("Is Ctrl Hold: %d"), playerComponent->IsCtrlHold);
				//playerComponent->InGamePrint(FString::Printf(TEXT("Is Ctrl Hold: %d"), playerComponent->IsCtrlHold));
				if (!playerComponent->IsCtrlHold) return;
				AFGCharacterPlayer* playerCharacter = Cast<AFGCharacterPlayer>(UGameplayStatics::GetPlayerCharacter(wire->GetWorld(), 0));
				//UFGInventoryComponent* playerInv = subsystem->GetPlayerCharacter()->GetInventory();
				UFGManufacturerClipboardRCO* clipboardRCO = playerController->GetRemoteCallObjectOfClass<UFGManufacturerClipboardRCO>();
				UFGCircuitConnectionComponent* con = wire->GetConnection(0);
				AFGBuildableFactory* factory = nullptr;
				AFGBuildableFactory* otherFactory = nullptr;
				//TSubclassOf<UFGRecipe> factoryRecipe = nullptr;
				//TSubclassOf<UFGRecipe> otherFactoryRecipe = nullptr;
				AFGBuildableManufacturer* manufacturer = nullptr;
				AFGBuildableManufacturer* otherManufacturer = nullptr;
				TArray<UWireRecipeCopierActorComponent*> factoryComponents;
				TArray<UWireRecipeCopierActorComponent*> otherFactoryComponents;

				if (IsValid(con))
				{
					factory = Cast<AFGBuildableFactory>(con->GetOuter());
					factory->GetComponents(factoryComponents, true);
					//if (factoryComponents.Num() > 0 && !IsValid(factoryComponents[0]->Subsystem)) factoryComponents[0]->Subsystem = module->Subsystem;
					//module->Subsystem->InGamePrint(FString::Printf(TEXT("Factory (%s) acquired"),*factory->GetName()));
					UFGCircuitConnectionComponent* otherCon = wire->GetOppositeConnection(con);
					if (IsValid(otherCon))
					{
						//UE_LOGFMT(LogWireRecipeCopier, Display, "otherCon: {0}", otherCon->GetName());
						otherFactory = Cast<AFGBuildableFactory>(otherCon->GetOuter());
						if (!IsValid(otherFactory)) return;		//UE_LOGFMT(LogWireRecipeCopier, Display, "otherFactory: {0}", otherFactory->GetName());
						otherFactory->GetComponents(otherFactoryComponents, true);
						//if(otherFactoryComponents.Num() > 0 && IsValid(otherFactoryComponents[0])) UE_LOGFMT(LogWireRecipeCopier, Display, "otherFactoryComponents: {0}", otherFactoryComponents[0]->GetName());
						//if (otherFactoryComponents.Num() > 0 && !IsValid(otherFactoryComponents[0]->Subsystem)) otherFactoryComponents[0]->Subsystem = module->Subsystem;
						//module->Subsystem->InGamePrint(FString::Printf(TEXT("Other Factory (%s) acquired"), *otherFactory->GetName()));
					}
				}
				//UE_LOGFMT(LogWireRecipeCopier, Display, "Before setting flag");
				int connectionFlag = 0;
				//UE_LOGFMT(LogWireRecipeCopier, Display, "After setting flag");
				FString factoryName = "";
				FString otherFactoryName = "";
				//bool IsValid(manufacturer) = false;
				//bool IsValid(otherManufacturer) = false;
				if (IsValid(factory))
				{
					//UE_LOGFMT(LogWireRecipeCopier, Display, "Setting factory");
					manufacturer = Cast<AFGBuildableManufacturer>(factory);
					factoryName = factory->mDisplayName.ToString();
					if ((IsValid(manufacturer) && factory->IsConfigured()) || (!IsValid(manufacturer) && factory->GetCurrentPotential() != 1.0))
					{
						connectionFlag += 2;
						//factoryRecipe = manufacturer->GetCurrentRecipe();
					}
					else connectionFlag += 1;
					//subsystem->InGamePrint(FString::Printf(TEXT("Current factory potential: %f"), factory->GetCurrentPotential()));
				}
				if (IsValid(otherFactory))
				{
					//UE_LOGFMT(LogWireRecipeCopier, Display, "Setting other factory");
					otherManufacturer = Cast<AFGBuildableManufacturer>(otherFactory);
					otherFactoryName = otherFactory->mDisplayName.ToString();
					if ((IsValid(otherManufacturer) && otherFactory->IsConfigured()) || (!IsValid(otherManufacturer) && otherFactory->GetCurrentPotential() != 1.0))
					{
						connectionFlag += 6;
						//otherFactoryRecipe = otherManufacturer->GetCurrentRecipe();
					}
					else connectionFlag += 3;
					//subsystem->InGamePrint(FString::Printf(TEXT("Current otherFactory potential: %f"), otherFactory->GetCurrentPotential()));
				}
				//UE_LOGFMT(LogWireRecipeCopier,Display, "Current flag: {0}", connectionFlag);
				switch (connectionFlag)
				{
				case 1:
					if (IsValid(manufacturer))
					{
						if (playerComponent->CopiedSettings.Contains(factoryName)) playerComponent->PasteSettings(manufacturer, factoryName);
					}
					else
					{
						if (playerComponent->CopiedPotentials.Contains(factoryName)) playerComponent->PastePotential(factory, factoryName);
					}
					break;
				case 2:
					if (IsValid(manufacturer))
					{
						playerComponent->CopySettings(manufacturer);
					}
					else
					{
						playerComponent->CopyPotential(factory);
					}
					break;
				case 3:
					if (IsValid(otherManufacturer))
					{
						if (playerComponent->CopiedSettings.Contains(otherFactoryName)) playerComponent->PasteSettings(otherManufacturer, otherFactoryName);
					}
					else
					{
						if (playerComponent->CopiedPotentials.Contains(otherFactoryName)) playerComponent->PastePotential(otherFactory, otherFactoryName);
					}
					break;
				case 4:
					if (IsValid(manufacturer))
					{
						if (playerComponent->CopiedSettings.Contains(factoryName)) playerComponent->PasteSettings(manufacturer, factoryName);
					}
					else
					{
						if (playerComponent->CopiedPotentials.Contains(factoryName)) playerComponent->PastePotential(factory, factoryName);
					}
					if (IsValid(otherManufacturer))
					{
						if (playerComponent->CopiedSettings.Contains(otherFactoryName)) playerComponent->PasteSettings(otherManufacturer, otherFactoryName);
					}
					else
					{
						if (playerComponent->CopiedPotentials.Contains(otherFactoryName)) playerComponent->PastePotential(otherFactory, otherFactoryName);
					}
					break;
				case 5:
					if (IsValid(manufacturer))
					{
						playerComponent->CopySettings(manufacturer);
					}
					else
					{
						playerComponent->CopyPotential(factory);
					}
					if (IsValid(otherManufacturer))
					{
						if (playerComponent->CopiedSettings.Contains(otherFactoryName)) playerComponent->PasteSettings(otherManufacturer, otherFactoryName);
					}
					else
					{
						if (playerComponent->CopiedPotentials.Contains(otherFactoryName)) playerComponent->PastePotential(otherFactory, otherFactoryName);
					}
					break;
				case 6:
					if (IsValid(otherManufacturer))
					{
						playerComponent->CopySettings(otherManufacturer);
					}
					else
					{
						playerComponent->CopyPotential(otherFactory);
					}
					break;
				case 7:
					if (IsValid(otherManufacturer))
					{
						playerComponent->CopySettings(otherManufacturer);
					}
					else
					{
						playerComponent->CopyPotential(otherFactory);
					}
					if (IsValid(manufacturer))
					{
						if (playerComponent->CopiedSettings.Contains(factoryName)) playerComponent->PasteSettings(manufacturer, factoryName);
					}
					else
					{
						if (playerComponent->CopiedPotentials.Contains(factoryName)) playerComponent->PastePotential(factory, factoryName);
					}
					break;
				case 8:
					if (IsValid(manufacturer))
					{
						playerComponent->CopySettings(manufacturer);
					}
					else
					{
						playerComponent->CopyPotential(factory);
					}
					if (IsValid(otherManufacturer))
					{
						if (playerComponent->CopiedSettings.Contains(otherFactoryName)) playerComponent->PasteSettings(otherManufacturer, otherFactoryName);
						else playerComponent->CopySettings(otherManufacturer);
					}
					else
					{
						if (playerComponent->CopiedPotentials.Contains(otherFactoryName)) playerComponent->PastePotential(otherFactory, otherFactoryName);
						else playerComponent->CopyPotential(otherFactory);
					}
					break;
				}
				//subsystem->InGamePrint(FString::FromInt(subsystem->GetPowerShardAmount()));
			}

			/*else if (IsValid(wire->GetConnection(1)))
			{
				UE_LOG(LogWireRecipeCopier, Display, TEXT("Connection 1: %s"), *wire->GetConnection(1)->GetName());
			}*/
		}

	}
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FWireRecipeCopierModule, WireRecipeCopier)