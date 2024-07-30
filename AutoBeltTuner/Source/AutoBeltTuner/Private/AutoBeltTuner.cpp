// Copyright Epic Games, Inc. All Rights Reserved.

#include "AutoBeltTuner.h"

#define LOCTEXT_NAMESPACE "FAutoBeltTunerModule"

DEFINE_LOG_CATEGORY(LogAutoBeltTuner);

void FAutoBeltTunerModule::StartupModule()
{
	if (!WITH_EDITOR)
	{
		SUBSCRIBE_METHOD_AFTER(UFGFactoryConnectionComponent::Factory_GrabOutput, &hook);
	}
}

void FAutoBeltTunerModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
}

void FAutoBeltTunerModule::hook(const bool& result, UFGFactoryConnectionComponent* self, FInventoryItem& out_item, float& out_OffsetBeyond, TSubclassOf<UFGItemDescriptor> type)
{
	//uint32 ThreadId = FPlatformTLS::GetCurrentThreadId();
				//UE_LOG(LogAutoBeltTuner,Display,TEXT("Running on %s"), *FThreadManager::Get().GetThreadName(ThreadId));
	AFGBuildable* buildable = self->GetOuterBuildable();
	if (IsValid(buildable) && buildable->IsA<AFGBuildableManufacturer>())
	{
		UAutoBeltTunerGameInstanceModule* module = Cast<UAutoBeltTunerGameInstanceModule>(buildable->GetGameInstance()->GetSubsystem<UGameInstanceModuleManager>()->FindModule(FName("AutoBeltTuner")));
		if (!IsValid(module->Subsystem)) return;
		AFGBuildableManufacturer* manufacturer = Cast< AFGBuildableManufacturer>(buildable);
		if (manufacturer->IsConfigured() && manufacturer->IsProducing())
		{
			TSubclassOf<UFGRecipe> recipe = manufacturer->GetCurrentRecipe();
			//for (UFGFactoryConnectionComponent* input : manufacturer->mFactoryInputConnections)
			//{
			UFGFactoryConnectionComponent* con = self->GetConnection();
			if (IsValid(recipe) && IsValid(con))
			{
				AFGBuildable* out = con->GetOuterBuildable();
				if (IsValid(out) && out->IsA<AFGBuildableConveyorBase>())
				{
					AFGBuildableConveyorBase* base = Cast<AFGBuildableConveyorBase>(out);
					if (IsValid(base))
					{
						//AFGBuildableConveyorBelt* belt = Cast< AFGBuildableConveyorBelt>(base);
						//AFGBuildableConveyorLift* lift = Cast<AFGBuildableConveyorLift>(base);
						TArray<UAutoBeltTunerActorComponent*> components;
						//if (IsValid(belt))
						//{
							base->GetComponents(components, true);
						/*}
						else if (IsValid(lift))
						{
							lift->GetComponents(components, true);
						}*/
						//UE_LOG(LogAutoBeltTuner, Display, TEXT("Component length: %d"), components.Num());
						if (base->mSpeed > 0)
						{
							//FString beltName = belt->mDisplayName.ToString();
							/*if (!module->Subsystem->BeltSpeeds.Contains(beltName))
							{
								module->Subsystem->BeltSpeeds.Emplace(beltName, belt->mSpeed);
							}*/
							float maxSpeed = Cast<AFGBuildableConveyorBase>(base->GetClass()->ClassDefaultObject)->mSpeed;

							for (FItemAmount& ia : UFGRecipe::GetIngredients(recipe))
							{
								if (ia.ItemClass == out_item.GetItemClass())
								{
									float speed = FMath::Min((float)ia.Amount * 120.0 * manufacturer->GetCurrentPotential() * manufacturer->GetManufacturingSpeed() / UFGRecipe::GetManufacturingDuration(recipe), maxSpeed);
									//UE_LOG(LogAutoBeltTuner, Display, TEXT("Belt: %s, Speed: %f, Max Speed: %f"), *beltName, speed, maxSpeed);
									//if (belt->mSpeed != speed) belt->mSpeed = speed;  //module->Subsystem->SetBeltSpeed(belt, speed);
									if (base->mSpeed != speed && components.Num() > 0)
									{
										components[0]->SetBeltSpeed_Server(speed);
										//module->Subsystem->SetBeltSpeed(belt, speed);
									}
									//UE_LOG(LogAutoBeltTuner, Display, TEXT("Speed: %f, Belt Speed: %f, Belt CDO Speed: %f"), speed, belt->mSpeed, beltCDO->mSpeed);
									break;
								}
							}
						}
					}
					
					//UE_LOG(LogAutoBeltTuner, Display, TEXT("Belt (%s) Set Speed Finished"), *belt->GetFName().ToString());
				}
			}

			//}
		}
		else
		{
			for (UFGFactoryConnectionComponent* input : manufacturer->mFactoryInputConnections)
			{
				UFGFactoryConnectionComponent* con = input->GetConnection();
				if (IsValid(con))
				{
					AFGBuildable* out = con->GetOuterBuildable();
					if (IsValid(out) && out->IsA<AFGBuildableConveyorBase>())
					{
						AFGBuildableConveyorBase* base = Cast<AFGBuildableConveyorBase>(out);
						//if (IsValid(base))
						//{
							//AFGBuildableConveyorBelt* belt = Cast< AFGBuildableConveyorBelt>(base);
							//AFGBuildableConveyorLift* lift = Cast<AFGBuildableConveyorLift>(base);
							TArray<UAutoBeltTunerActorComponent*> components;
							//if (IsValid(belt))
							//{
							base->GetComponents(components, true);
							/*}
							else if (IsValid(lift))
							{
								lift->GetComponents(components, true);
							}*/
							//UE_LOG(LogAutoBeltTuner, Display, TEXT("Belt (%s) Set Default Speed Started"), *belt->GetFName().ToString());
							//FString beltName = belt->mDisplayName.ToString();
							float maxSpeed = Cast<AFGBuildableConveyorBase>(base->GetClass()->ClassDefaultObject)->mSpeed;
							/*if (!module->Subsystem->BeltSpeeds.Contains(beltName))
							{
								module->Subsystem->BeltSpeeds.Emplace(beltName, belt->mSpeed);
							}
							else
							{*/
							//if (belt->mSpeed != maxSpeed) belt->mSpeed = maxSpeed;
							if (base->mSpeed != maxSpeed && components.Num() > 0)
							{
								components[0]->SetBeltSpeed_Server(maxSpeed);
								//module->Subsystem->SetBeltSpeed(belt, maxSpeed);
							}
						//}
						
						//}
						//UE_LOG(LogAutoBeltTuner, Display, TEXT("Belt (%s) Set Default Speed Finished"), *belt->GetFName().ToString());
					}
				}
			}
		}
	}
}



#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FAutoBeltTunerModule, AutoBeltTuner)