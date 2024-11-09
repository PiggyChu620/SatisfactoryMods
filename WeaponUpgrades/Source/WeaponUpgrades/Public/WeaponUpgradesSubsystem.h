// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystem/ModSubsystem.h"
#include "SessionSettings/SessionSettingsManager.h"
#include "WeaponUpgrades.h"
#include "WeaponUpgradesBPFL.h"
#include "Equipment/FGAmmoTypeInstantHit.h"
#include "Resources/FGEquipmentDescriptor.h"
#include <FGRadialDamageType.h>
#include <FGPointDamageType.h>
#include <FGAmmoTypeSpreadshot.h>
#include <StructuredLog.h>
#include <AssetRegistry/AssetRegistryModule.h>
#include "FGSchematic.h"
#include "FGSchematicManager.h"

#include "WeaponUpgradesSubsystem.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct FAmmoUpgrade
{
	GENERATED_BODY()

public:
	UPROPERTY()
	UFGAmmoType* Ammo;

	UPROPERTY()
	double Value;

	FAmmoUpgrade(){}

	FAmmoUpgrade(UFGAmmoType* ammo, double value) :Ammo(ammo), Value(value)
	{
	}
};

UCLASS()
class WEAPONUPGRADES_API AWeaponUpgradesSubsystem : public AModSubsystem
{
	GENERATED_BODY()
	
public:
	AWeaponUpgradesSubsystem();
	~AWeaponUpgradesSubsystem();

	TArray<UFGAmmoType*> Ammos;
	TMap<UFGAmmoType*, double> BaseDamages;
	TMap<UFGAmmoType*, double> BaseExplotionDamages;
	TMap<UFGAmmoType*, double> BaseSizes;
	TMap<UFGAmmoType*, double> BaseFireRates;
	TMap<UFGAmmoType*, double> BaseRadiuses;
	TMap<UFGAmmoType*, double> BaseShatterAmounts;
	TMap<UFGAmmoType*, double> BaseStunDurations;

	UPROPERTY(Replicated, ReplicatedUsing = SetAllDamages)
	TArray<FAmmoUpgrade> UpgradedDamages;

	UPROPERTY(Replicated, ReplicatedUsing = SetAllFireRates)
	TArray<FAmmoUpgrade> UpgradedFireRates;

	UPROPERTY(Replicated, ReplicatedUsing = SetAllSizes)
	TArray<FAmmoUpgrade> UpgradedSizes;

	UPROPERTY(Replicated, ReplicatedUsing = SetAllExplosiveDamages)
	TArray<FAmmoUpgrade> UpgradedExposionDamages;

	UPROPERTY(Replicated, ReplicatedUsing = SetAllExplosiveRadius)
	TArray<FAmmoUpgrade> UpgradedExposionRadiuses;

	UPROPERTY(Replicated, ReplicatedUsing = SetAllShatterAmounts)
	TArray<FAmmoUpgrade> UpgradedShatterAmounts;

	UPROPERTY(BlueprintReadWrite, SaveGame, Category = "Weapon Upgrades")
	double BaseValue = 50.0*(FMath::Sqrt(5.0)-1);

	UPROPERTY(BlueprintReadWrite, SaveGame, Category = "Weapon Upgrades")
	bool IsExponentialProgression = true;

	//UPROPERTY(BlueprintReadWrite, SaveGame, Category = "Weapon Upgrades")
	//double RifleDamageMultiplier=1.0;

	//UPROPERTY(BlueprintReadWrite, SaveGame, Category = "Weapon Upgrades")
	//double RifleMagazineMultiplier = 1.0;

	//UPROPERTY(BlueprintReadWrite, SaveGame, Category = "Weapon Upgrades")
	//double RifleFirerateMultiplier = 1.0;

	//UPROPERTY(BlueprintReadWrite, SaveGame, Category = "Weapon Upgrades")
	//double RebarDamageMultiplier = 1.0;

	UPROPERTY(BlueprintReadWrite, Category = "Weapon Upgrades")
	AFGSchematicManager* SchematicManager;

	UPROPERTY(BlueprintReadWrite, Category = "Weapon Upgrades")
	TArray<TSubclassOf<UFGSchematic>> DamageSchematics;

	UPROPERTY(BlueprintReadWrite, Category = "Weapon Upgrades")
	TArray<TSubclassOf<UFGSchematic>> SizeSchematics;

	UPROPERTY(BlueprintReadWrite, Category = "Weapon Upgrades")
	TArray<TSubclassOf<UFGSchematic>> FireRateSchematics;

	UPROPERTY(BlueprintReadWrite, Category = "Weapon Upgrades")
	TArray<TSubclassOf<UFGSchematic>> ExplosionDamageSchematics;

	UPROPERTY(BlueprintReadWrite, Category = "Weapon Upgrades")
	TArray<TSubclassOf<UFGSchematic>> ExplosionRadiusSchematics;

	UPROPERTY(BlueprintReadWrite, Category = "Weapon Upgrades")
	TArray<TSubclassOf<UFGSchematic>> ShatterAmountSchematics;

	//UPROPERTY(BlueprintReadWrite, Category = "Weapon Upgrades")
	//TArray<TSubclassOf<UFGSchematic>> DamageSchematics;


	UPROPERTY(BlueprintReadWrite, SaveGame, Category = "Weapon Upgrades")
	double RebarMagazineMultiplier = 1.0;

	UPROPERTY(BlueprintReadWrite, SaveGame, Category = "Weapon Upgrades")
	double ExplosionRadiusMultiplier = 1.0;

	UPROPERTY(BlueprintReadWrite, Category = "Weapon Upgrades")
	AFGProjectile* BP_Rebar_Stunshot;

	UPROPERTY(BlueprintReadWrite, Category = "Weapon Upgrades")
	TSubclassOf<UFGEquipmentDescriptor> Rifle;

	UPROPERTY(BlueprintReadWrite, Category = "Weapon Upgrades")
	TSubclassOf<UFGEquipmentDescriptor> RebarGun;


	UFUNCTION(BlueprintCallable, Category = "Weapon Upgrades")
	double GetMultiplier(double level);


	UFUNCTION(BlueprintCallable, Category = "Weapon Upgrades")
	void SetAllDamages_Server();

	UFUNCTION()
	void SetAllDamages();

	UFUNCTION(BlueprintCallable, Category = "Weapon Upgrades")
	void SetAllFireRates_Server();

	UFUNCTION()
	void SetAllFireRates();

	UFUNCTION(BlueprintCallable, Category = "Weapon Upgrades")
	void SetAllSizes_Server();

	UFUNCTION()
	void SetAllSizes();

	UFUNCTION(BlueprintCallable, Category = "Weapon Upgrades")
	void SetAllExplosiveDamages_Server();

	UFUNCTION()
	void SetAllExplosiveDamages();

	UFUNCTION(BlueprintCallable, Category = "Weapon Upgrades")
	void SetAllExplosiveRadius_Server();

	UFUNCTION()
	void SetAllExplosiveRadius();

	UFUNCTION(BlueprintCallable, Category = "Weapon Upgrades")
	void SetAllShatterAmounts_Server();

	UFUNCTION()
	void SetAllShatterAmounts();

	UFUNCTION(BlueprintImplementableEvent, Category = "Weapon Upgrades")
	void SetStunDuration(double duration);

	UFUNCTION(BlueprintImplementableEvent, Category = "Weapon Upgrades")
	double GetStunDuration();


	void Init();

	void GetAllAmmo();

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

protected:
	virtual void BeginPlay() override;

private:
	static bool isExplosive(const UFGDamageType* type);
	static bool isPointDamage(const UFGDamageType* type);
	bool isRifleAmmo(const UFGAmmoType* ammo);
	bool isRebarAmmo(const UFGAmmoType* ammo);
	double getTotalExplosiveDamage(const UFGAmmoType* ammo);
	double getTotalExplosiveRadius(const UFGAmmoType* ammo);
	double getTotalPointDamage(const UFGAmmoType* ammo);
	void setExplosiveDamage(UFGAmmoType* ammo, double damage);
	void setExplosiveRadius(UFGAmmoType* ammo, double radius);
	void setPointDamage(UFGAmmoType* ammo, double damage);
	void setShatterAmount(UFGAmmoType* ammo, double amount);
	double getShematicLevel(const TArray<TSubclassOf<UFGSchematic>>& schematic);
};
