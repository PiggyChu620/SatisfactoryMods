// Fill out your copyright notice in the Description page of Project Settings.


#include "FGBuildableFuelManufacturer.h"
#include "FGInventoryLibrary.h"

// Sets default values
AFGBuildableFuelManufacturer::AFGBuildableFuelManufacturer()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AFGBuildableFuelManufacturer::BeginPlay()
{
	if (HasAuthority()) 
	{
		/*inputInvComp = GetInputInventory();
		outputInvComp = GetOutputInventory();*/

		InputBuffer->SetLocked(false);
		InputBuffer->Resize(1);
		OutputBuffer->SetLocked(false);
		OutputBuffer->Resize(1);
		FuelBuffer->SetLocked(false);
		FuelBuffer->Resize(1);
		InputConnection0->SetInventory(InputBuffer);
		InputConnection1->SetInventory(FuelBuffer);
		OutputConnection->SetInventory(OutputBuffer);
		/*InputConnection0->GetInventory()->SetLocked(false);
		InputConnection1->GetInventory()->SetLocked(false);*/
		//OutputConnection->GetInventory()->SetLocked(false);
		InputConnection0->SetInventoryAccessIndex(0);
		InputConnection1->SetInventoryAccessIndex(0);
		OutputConnection->SetInventoryAccessIndex(0);
	}

	Super::BeginPlay();
	
}

bool AFGBuildableFuelManufacturer::ShouldSave_Implementation() const
{
	return true;
}
void AFGBuildableFuelManufacturer::Factory_CollectInput_Implementation()
{
	if (HasAuthority() && IsConfigured())
	{
		//int emptyIndex = InputBuffer->FindEmptyIndex();
		//UE_LOG(LogSatisFactorio, Display, TEXT("Empty Index: %d"), emptyIndex);
		
		//UE_LOG(LogSatisFactorio, Display, TEXT("Empty Fuel Index: %d"), emptyFuelIndex);
		FInventoryItem fuelItem, ingItem;
		TArray<FInventoryItem> outItems0, outItems1;

		if(InputConnection0->IsConnected()) InputConnection0->Factory_PeekOutput(outItems0);
		if(InputConnection1->IsConnected()) InputConnection1->Factory_PeekOutput(outItems1);
		
		if(InputConnection0->IsConnected() && outItems0.Num() > 0)
		{
			if(isFuel(outItems0[0]))
			{
				InputConnection0->SetInventory(FuelBuffer);
				InputConnection1->SetInventory(InputBuffer);
				fuelInput = InputConnection0;
				ingInput = InputConnection1;
				if(InputConnection0->IsConnected()) grabFuel(outItems0[0]);
				if(InputConnection1->IsConnected() && outItems1.Num() > 0 && isIngredient(outItems1[0]))
				{
					grabIngredient(outItems1[0]);
				}
			}
			else
			{
				InputConnection0->SetInventory(InputBuffer);
				InputConnection1->SetInventory(FuelBuffer);
				ingInput = InputConnection0;
				fuelInput = InputConnection1;
				if (InputConnection0->IsConnected() && isIngredient(outItems0[0])) grabIngredient(outItems0[0]);
				if(InputConnection1->IsConnected() && outItems1.Num() > 0 && isFuel(outItems1[0]))
				{
					grabFuel(outItems1[0]);
				}
			}
		}
		else if(InputConnection1->IsConnected() && outItems1.Num() > 0)
		{
			if (isFuel(outItems1[0]))
			{
				InputConnection0->SetInventory(InputBuffer);
				InputConnection1->SetInventory(FuelBuffer);
				ingInput = InputConnection0;
				fuelInput = InputConnection1;
				grabFuel(outItems1[0]);
			}
			else if (isIngredient(outItems1[0]))
			{
				InputConnection0->SetInventory(FuelBuffer);
				InputConnection1->SetInventory(InputBuffer);
				fuelInput = InputConnection0;
				ingInput = InputConnection1;
				grabIngredient(outItems1[0]);
			}
		}
		

		if (FuelBuffer->IsEmpty())
		{
			DebugFuelName = FText::FromString("N/A");
			DebugFuelAmount = 0;
			//UE_LOG(LogSatisFactorio, Display, TEXT("Fuel Amount: %d"), DebugFuelAmount);
		}
		else
		{
			FInventoryStack stack;

			FuelBuffer->GetStackFromIndex(0, stack);
			DebugFuelName = UFGItemDescriptor::GetItemName(stack.Item.GetItemClass());
			DebugFuelAmount = stack.NumItems;
			if (oldAmount != DebugFuelAmount)
			{
				oldAmount = DebugFuelAmount;
				OnAmountChanged(oldAmount);
				//UE_LOGFMT(LogSatisFactorio, Display, "OnAmountChanged called");
			}
			DebugFuelImage = UFGItemDescriptor::GetSmallIcon(stack.Item.GetItemClass());
			if (oldImage != DebugFuelImage)
			{
				oldImage = DebugFuelImage;
				DebugCycleTime = FMath::RoundUpToClosestMultiple((double)fuelEnergy / (double)mEnergyNeeded,.01f);
				OnFuelChanged(oldImage);
				//UE_LOGFMT(LogSatisFactorio, Display, "OnFuelChanged called");
			}
			//UE_LOG(LogSatisFactorio, Display, TEXT("Fuel: %s"), *stack.Item.GetItemClass()->GetName());
			//UE_LOG(LogSatisFactorio, Display, TEXT("Fuel Amount: %d"), DebugFuelAmount);
		}
		//if (InputBuffer->IsEmpty())
		//{
		//	DebugIngName = FText::FromString("N/A");
		//	DebugIngAmount = 0;
		//	//UE_LOG(LogSatisFactorio, Display, TEXT("Ingredient Amount: %d"), DebugIngAmount);
		//}
		//else
		//{
		//	FInventoryStack stack;

		//	InputBuffer->GetStackFromIndex(0, stack);
		//	DebugIngName = UFGItemDescriptor::GetItemName(stack.Item.GetItemClass());
		//	DebugIngAmount = stack.NumItems;
		//	//UE_LOG(LogSatisFactorio, Display, TEXT("Ingredient: %s"), *stack.Item.GetItemClass()->GetName());
		//	//UE_LOG(LogSatisFactorio, Display, TEXT("Ingredient Amount: %d"), DebugIngAmount);
		//}
	}
}

//bool AFGBuildableFuelManufacturer::Factory_GrabOutput_Implementation(UFGFactoryConnectionComponent* connection, FInventoryItem& out_item, float& out_OffsetBeyond, TSubclassOf<UFGItemDescriptor> type)
//{
//	UE_LOGFMT(LogSatisFactorio, Display, "Checking GrabOutput...");
//	if (UFGItemDescriptor::GetEnergyValue(out_item.GetItemClass())>0) return true;
//	for (FItemAmount& ia : UFGRecipe::GetIngredients(GetCurrentRecipe()))
//	{
//		if (ia.ItemClass == out_item.GetItemClass()) return true;
//	}
//	return false;
//}

bool AFGBuildableFuelManufacturer::CanProduce_Implementation() const
{
	if (FuelBuffer->IsEmpty() || InputBuffer->IsEmpty()) return false;
	return true;
}
// Called every frame
void AFGBuildableFuelManufacturer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (CanProduce() && fuelIndex>=0 && fuelEnergy>0)
	{
		DebugFuelProgress -= (double)DeltaTime * (double)mEnergyNeeded / (double)fuelEnergy;
		if (DebugFuelProgress <= 0)
		{
			FuelBuffer->RemoveFromIndex(fuelIndex, 1);
			DebugFuelProgress+=1.0;
		}
		OnProgressChanged(DebugFuelProgress);
	}
	//UE_LOGFMT(LogSatisFactorio, Display, "Ticking... ({0},)", DebugFuelProgress);
}

bool AFGBuildableFuelManufacturer::isFuel(FInventoryItem& item)
{
	fuelEnergy = UFGItemDescriptor::GetEnergyValue(item.GetItemClass());
	return fuelEnergy > 0;
}

bool AFGBuildableFuelManufacturer::isIngredient(FInventoryItem& item)
{
	for (FItemAmount& ia : UFGRecipe::GetIngredients(GetCurrentRecipe()))
	{
		if (ia.ItemClass == item.GetItemClass()) return true;
	}
	return false;
}

void AFGBuildableFuelManufacturer::grabFuel(FInventoryItem& item)
{
	int emptyFuelIndex = FuelBuffer->FindEmptyIndex();
	float out_OffsetBeyond = 100.f;

	if (emptyFuelIndex < 0)
	{
		emptyFuelIndex = FuelBuffer->FindFirstIndexWithItemType(item.GetItemClass());
		fuelIndex = emptyFuelIndex;
	}
	if (emptyFuelIndex < 0) return;

	FInventoryStack stack = UFGInventoryLibrary::MakeInventoryStack(1, item);
	FuelBuffer->SetLocked(false);
	int amountAdded=FuelBuffer->AddStackToIndex(emptyFuelIndex, stack, true);

	if (amountAdded>0)
	{
		fuelInput->Factory_GrabOutput(item, out_OffsetBeyond);

	}
}

void AFGBuildableFuelManufacturer::grabIngredient(FInventoryItem& item)
{
	int emptyIndex = InputBuffer->FindEmptyIndex();
	float out_OffsetBeyond = 100.f;

	if (emptyIndex < 0)
	{
		emptyIndex = InputBuffer->FindFirstIndexWithItemType(item.GetItemClass());
		ingIndex = emptyIndex;
	}
	if (emptyIndex < 0) return;

	FInventoryStack stack = UFGInventoryLibrary::MakeInventoryStack(1, item);
	InputBuffer->SetLocked(false);
	int amountAdded = InputBuffer->AddStackToIndex(emptyIndex, stack, false);
	if (amountAdded > 0)
	{
		ingInput->Factory_GrabOutput(item, out_OffsetBeyond);
	}
}



