// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include <CoreMinimal.h>
#include <Kismet/BlueprintFunctionLibrary.h>
#include "GameFramework/Actor.h"
#include "Components/SphereComponent.h"
#include "FGProjectile.h"
#include "FGDamageOverTime.h"
#include "FGDotComponent.h"
#include "FGDestructiveProjectile.h"
#include "Equipment/FGWeapon.h"
#include "Equipment/FGAmmoType.h"
#include "Equipment/FGAmmoTypeProjectile.h"
#include "Equipment/FGEquipmentStunSpear.h"
#include "Resources/FGEquipmentDescriptor.h"

#include "WeaponUpgradesBPFL.generated.h"



UCLASS()
class WEAPONUPGRADES_API UWeaponUpgradesBPFL : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

	/*friend class AFGWeapon;
	friend class UFGAMmoType;*/

	//inline static UFGAmmoType* tempAmmo;
	
	UFUNCTION(BlueprintCallable, Category = "Weapon Upgrades BPFL")
	static float SetAmmoDamage(UFGAmmoType* ammo, int index, float damage);
	//inline static UFGAmmoType* tempAmmo;

	UFUNCTION(BlueprintCallable, Category = "Weapon Upgrades BPFL")
	static float GetAmmoDamage(UFGAmmoType* ammo, int index);

	UFUNCTION(BlueprintCallable, Category = "Weapon Upgrades BPFL")
	static float SetExplosiveDamage(UFGAmmoTypeProjectile* ammo, int index, float damage);

	UFUNCTION(BlueprintCallable, Category = "Weapon Upgrades BPFL")
	static float GetExplosiveDamage(UFGAmmoTypeProjectile* ammo, int index);

	UFUNCTION(BlueprintCallable, Category = "Weapon Upgrades BPFL")
	static float SetExplosiveRadius(UFGAmmoTypeProjectile* ammo, int index, float cm);

	UFUNCTION(BlueprintCallable, Category = "Weapon Upgrades BPFL")
	static float GetExplosiveRadius(UFGAmmoTypeProjectile* ammo, int index);

	UFUNCTION(BlueprintCallable, Category = "Weapon Upgrades BPFL")
	static float SetExplosionRadius(UFGAmmoType* ammo, int index, float cm);

	UFUNCTION(BlueprintCallable, Category = "Weapon Upgrades BPFL")
	static float GetExplosionRadius(UFGAmmoType* ammo, int index);

	/*UFUNCTION(BlueprintCallable, Category = "Weapon Upgrades BPFL")
	static float SetWeaponReloadTime(UFGEquipmentDescriptor* equip, float seconds);*/

	UFUNCTION(BlueprintCallable, Category = "Weapon Upgrades BPFL")
	static int SetProjectileClusterAmount(AFGProjectile* ammo, int amount);

	UFUNCTION(BlueprintCallable, Category = "Weapon Upgrades BPFL")
	static int GetProjectileClusterAmount(AFGProjectile* ammo);

	UFUNCTION(BlueprintCallable, Category = "Weapon Upgrades BPFL")
	static float SetProjectileDamage(AFGProjectile* ammo, int index, float damage);

	UFUNCTION(BlueprintCallable, Category = "Weapon Upgrades BPFL")
	static float GetProjectileDamage(AFGProjectile* ammo, int index);

	UFUNCTION(BlueprintCallable, Category = "Weapon Upgrades BPFL")
	static float SetDOTDamage(UFGDamageOverTime* dot, float damage);

	UFUNCTION(BlueprintCallable, Category = "Weapon Upgrades BPFL")
	static float GetDOTDamage(UFGDamageOverTime* dot);

	UFUNCTION(BlueprintCallable, Category = "Weapon Upgrades BPFL")
	static float SetDestructiveRadius(AFGDestructiveProjectile* ammo, float radius);

	UFUNCTION(BlueprintCallable, Category = "Weapon Upgrades BPFL")
	static float GetDestructiveRadius(AFGDestructiveProjectile* ammo);

	UFUNCTION(BlueprintCallable, Category = "Weapon Upgrades BPFL")
	static float SetStunSpearDamage(AFGEquipmentStunSpear* ammo, int index, float damage);

	UFUNCTION(BlueprintCallable, Category = "Weapon Upgrades BPFL")
	static float GetStunSpearDamage(AFGEquipmentStunSpear* ammo, int index);

	/*UFUNCTION(BlueprintCallable, Category = "Weapon Upgrades BPFL")
	static UFGDotComponent* MakeFGDotComponent(TSubclassOf<UFGDamageOverTime> dot);*/
};
