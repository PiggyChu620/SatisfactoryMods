// Fill out your copyright notice in the Description page of Project Settings.

#include "AHiddenTreasuresModSubsystem.h"
#include "HiddenTreasures.h"
#include <StructuredLog.h>

//DEFINE_LOG_CATEGORY(LogHiddenTreasures);

AHiddenTreasuresModSubsystem::AHiddenTreasuresModSubsystem()
{
	
}

AHiddenTreasuresModSubsystem::~AHiddenTreasuresModSubsystem()
{
}

void AHiddenTreasuresModSubsystem::BeginPlay()
{
	Super::BeginPlay();
	/*
	for (FItemDropWithChance& item : Items)
	{
		UFGItemDescriptor* cdo = Cast< UFGItemDescriptor>(item.Drop.ItemClass->GetClass()->ClassDefaultObject);
		if (IsValid(cdo) && cdo->mResourceSinkPoints != 0)
		{
			float c = item.DropChance;
			item.DropChance = .001f / (float)cdo->mResourceSinkPoints;
			UE_LOG(LogHiddenTreasures, Display, TEXT("Change drop chance of %s from %f to %f"), *cdo->mDisplayName.ToString(),c, item.DropChance);
		}
	}
*/
	//eventSubsystem = GetWorld()->GetSubsystem<AFGEventSubsystem>();
	if (EventSubsystem->GetCurrentEvents().Contains(EEvents::EV_Christmas)) IsFicsmas = true;
	else IsFicsmas = false;

	SUBSCRIBE_METHOD_AFTER(UFGFoliageLibrary::CheckInventorySpaceAndGetStacks, [](const bool& result, AFGCharacterPlayer* character, UHierarchicalInstancedStaticMeshComponent* meshComponent, TArrayView< uint32 > randomSeeds, TArray<struct FInventoryStack>& out_inventoryStacks)
		{
			//UE_LOGFMT(LogHiddenTreasures, Display, "Hook called");
			UWorld* world = character->GetWorld();
			//UE_LOGFMT(LogHiddenTreasures, Display, "Getting World...");
			if (IsValid(world))
			{
				//UE_LOGFMT(LogHiddenTreasures, Display, "The World is valid");
				AHiddenTreasuresModSubsystem* subsystem = AHiddenTreasuresModSubsystem::Get(world);
				//UE_LOGFMT(LogHiddenTreasures, Display, "Checking Subsystem...");
				if (IsValid(subsystem))
				{
					FString log = TEXT("Equipment Multiplier : {0}");
					//subsystem->Count = 0;
					//UE_LOGFMT(LogHiddenTreasures, Display, "The Subsystem is valid");
					for (FItemDropWithChance& item : subsystem->Items)
					{
						if (UFGItemDescriptor::GetCategory(item.Drop.ItemClass) != subsystem->FICSMAS || subsystem->IsFicsmas)
						{
							/*if (subsystem->ItemPoints.Contains(item.Drop.ItemClass))
							{
								UE_LOGFMT(LogHiddenTreasures, Display, "Item: {0}, Point: {1}, Min: {2}", item.Drop.ItemClass->GetName(), subsystem->ItemPoints[item.Drop.ItemClass], subsystem->MinSinkPoint);
							}*/
							UFGItemDescriptor* cdo = item.Drop.ItemClass.GetDefaultObject();

							if (!subsystem->ItemPoints.Contains(item.Drop.ItemClass) || subsystem->ItemPoints[item.Drop.ItemClass] > subsystem->MinSinkPoint)
							{
								//UE_LOGFMT(LogHiddenTreasures, Display, "Base Drop Chance: {0}", subsystem->DropChance);
								double dropChance = subsystem->DropChance / item.DropChance;

								if (cdo->IsA<UFGEquipmentDescriptor>())
								{
									
									//subsystem->InGamePrint(FString::Format(*log, { subsystem->EqupmentMultiplier }));
									//UE_LOGFMT(LogHiddenTreasures, Display, "Equipment Multiplier: {0}", subsystem->EqupmentMultiplier);
									if (subsystem->EqupmentMultiplier > 0.0)
									{
										dropChance *= subsystem->EqupmentMultiplier;
										if (IsValid(item.Drop.ItemClass) && FMath::RandRange(0.0, 1.0) <= dropChance)
										{
											out_inventoryStacks.Emplace(FInventoryStack(FMath::RandRange(1, 1), item.Drop.ItemClass));
										}
									}
								}
								else if (IsValid(item.Drop.ItemClass) && FMath::RandRange(0.0, 1.0) <= dropChance)
								{
									//UE_LOGFMT(LogHiddenTreasures, Display, "{0} is added to the drop", item.Drop.ItemClass->GetName());
									out_inventoryStacks.Emplace(FInventoryStack(FMath::RandRange(item.Drop.NumItems.Min, item.Drop.NumItems.Max), item.Drop.ItemClass));
								}
							}
							//subsystem->Count++;
						}
					}
					//UE_LOGFMT(LogHiddenTreasures, Display, "Count: {0}",subsystem->Count);
				}
			}
		});
		
}


void AHiddenTreasuresModSubsystem::GetAllSinkableItems()
{
	TArray<UClass*> nativeRootClasses;
	TArray<FTopLevelAssetPath> nativeRootClassPaths;
	GetDerivedClasses(UFGItemDescriptor::StaticClass(), nativeRootClasses);
	nativeRootClasses.Add(UFGItemDescriptor::StaticClass());

	for (UClass* obj : nativeRootClasses)
	{
		if (IsValid(obj) && obj->HasAnyClassFlags(CLASS_Native))
		{
			nativeRootClassPaths.Add(obj->GetClassPathName());
			
		}
	}

	TSet<FTopLevelAssetPath> allItems;
	IAssetRegistry::Get()->GetDerivedClassNames(nativeRootClassPaths, {}, allItems);
	allItems.Append(nativeRootClassPaths);

	for (FTopLevelAssetPath data : allItems)
	{
		//UE_LOGFMT(LogHiddenTreasures, Display, "Checking {0}", *data.GetAssetName().ToString());
		TSubclassOf<UFGItemDescriptor> item= TSoftClassPtr<UFGItemDescriptor>(FSoftObjectPath(data)).Get();
		bool alreadyAdded= Items.FindByPredicate([item](const FItemDropWithChance ic)
		{
				return ic.Drop.ItemClass == item;
		})!=nullptr;
		
		if (!BannedItems.Contains(item) && !alreadyAdded)
		{
			UFGItemDescriptor* cdo = item.GetDefaultObject();
			if (IsValid(item) && IsValid(cdo))
			{
				//FResourceSinkPointsData* sinkPoint = SinkPoints->FindRow<FResourceSinkPointsData>(*cdo->mDisplayName.ToString(), "", false);
				//UFGItemDescriptor* cdo = Cast<UFGItemDescriptor>(item->GetClass()->ClassDefaultObject);
				int32 point = ResourceSinkSubsystem->GetResourceSinkPointsForItem(item);
				FInt32Interval amount = FInt32Interval(1, 10);
				//double em = 1.0;
				//if (sinkPoint)
				//{
					//UE_LOGFMT(LogHiddenTreasures, Display, "Min Sink Point: {0}", MinSinkPoint);
				
				if (point > 0 && UFGItemDescriptor::GetRadioactiveDecay(item) == 0 && cdo->mStackSize != EStackSize::SS_FLUID)
				{
					FItemDrop drop = FItemDrop();
					FItemDropWithChance chance = FItemDropWithChance();
					float dropChance = FMath::Sqrt((double)point);

					/*if (UFGItemDescriptor::GetCategory(item) != FICSMAS || isFicsmas)
					{*/
						ItemPoints.Emplace(item, point);
						/*if (cdo->IsA<UFGEquipmentDescriptor>())
						{
							em = EqupmentMultiplier;
							if (em > 0.0)
							{
								amount = FInt32Interval(1, 1);
								drop.ItemClass = item;
								drop.NumItems = amount;
								chance.Drop = drop;
								chance.DropChance = dropChance * em;

								Items.Emplace(chance);
							}
						}
						else
						{*/
							drop.ItemClass = item;
							drop.NumItems = amount;
							chance.Drop = drop;
							chance.DropChance = dropChance;

							Items.Emplace(chance);

						//}
					//}

					//UE_LOGFMT(LogHiddenTreasures, Display, "{0} added to the array with chance of {1}", item->GetName(), dropChance);
				}
				//}
			}
		}
		
	}
}
