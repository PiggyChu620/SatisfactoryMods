// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "SatisFactorio.h"
#include "Buildables/FGBuildableManufacturer.h"
#include "FGFactoryConnectionComponent.h"
#include "Resources/FGItemDescriptor.h"
#include "FGSatisFactorioFCC.h"

#include "FGBuildableFuelManufacturer.generated.h"

UCLASS()
class SATISFACTORIO_API AFGBuildableFuelManufacturer : public AFGBuildableManufacturer
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFGBuildableFuelManufacturer();

	UPROPERTY(BlueprintReadWrite, Category = "SatisFactorio")
	UFGFactoryConnectionComponent* InputConnection0;

	UPROPERTY(BlueprintReadWrite, Category = "SatisFactorio")
	UFGFactoryConnectionComponent* InputConnection1;

	UPROPERTY(BlueprintReadWrite, Category = "SatisFactorio")
	UFGFactoryConnectionComponent* OutputConnection;

	UPROPERTY(BlueprintReadWrite, Category = "SatisFactorio")
	UFGInventoryComponent* InputBuffer;

	UPROPERTY(BlueprintReadWrite, Category = "SatisFactorio")
	UFGInventoryComponent* OutputBuffer;

	UPROPERTY(BlueprintReadWrite, Category = "SatisFactorio")
	UFGInventoryComponent* FuelBuffer;

	UPROPERTY(EditAnywhere, Category = "SatisFactorio")
	float mEnergyNeeded;

	//Debug infos
	UPROPERTY(BlueprintReadWrite, Category = "SatisFactorio")
	FText DebugFuelName;

	UPROPERTY(BlueprintReadWrite, Category = "SatisFactorio")
	int DebugFuelAmount;

	UPROPERTY(BlueprintReadWrite, Category = "SatisFactorio")
	FText DebugIngName;

	UPROPERTY(BlueprintReadWrite, Category = "SatisFactorio")
	int DebugIngAmount;

	UPROPERTY(BlueprintReadWrite, Category = "SatisFactorio")
	UTexture2D* DebugFuelImage;

	UPROPERTY(BlueprintReadWrite, Category = "SatisFactorio")
	double DebugFuelProgress=1.0;

	UPROPERTY(BlueprintReadWrite, Category = "SatisFactorio")
	double DebugCycleTime = 0.0;

	UPROPERTY(BlueprintReadWrite, Category = "SatisFactorio")
	TArray<TSubclassOf<UFGItemDescriptor>> RelevantItems;

	UFUNCTION(BlueprintImplementableEvent, Category = "SatisFactorio")
	void OnProgressChanged(double p);

	UFUNCTION(BlueprintImplementableEvent, Category = "SatisFactorio")
	void OnFuelChanged(UTexture2D* img);

	UFUNCTION(BlueprintImplementableEvent, Category = "SatisFactorio")
	void OnAmountChanged(int amount);


protected:

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual bool ShouldSave_Implementation() const override;
	virtual void Factory_CollectInput_Implementation();
	//virtual bool Factory_GrabOutput_Implementation(class UFGFactoryConnectionComponent* connection, FInventoryItem& out_item, float& out_OffsetBeyond, TSubclassOf< UFGItemDescriptor > type) override;
	virtual bool CanProduce_Implementation() const override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	UFGFactoryConnectionComponent* fuelInput;
	UFGFactoryConnectionComponent* ingInput;
	void grabFuel(FInventoryItem& item);
	void grabIngredient(FInventoryItem& item);
	bool isFuel(FInventoryItem& item);
	bool isIngredient(FInventoryItem& item);
	float fuelEnergy;
	int fuelIndex;
	int ingIndex;
	UTexture2D* oldImage = nullptr;
	int oldAmount = 0;
};
