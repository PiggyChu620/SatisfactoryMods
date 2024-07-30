#include "WeaponUpgradesBPFL.h"
#include "WeaponUpgrades.h"
#include "FGProjectile.h"
#include "FGDamageOverTime.h"
#include "FGDotComponent.h"
#include "FGDestructiveProjectile.h"
#include "Components/SphereComponent.h"
#include "Equipment/FGWeapon.h"
#include "Equipment/FGAmmoType.h"
#include "Equipment/FGAmmoTypeProjectile.h"
#include "Equipment/FGEquipmentStunSpear.h"
#include "Resources/FGEquipmentDescriptor.h"
#include "DamageTypes/FGDamageType.h"
#include "DamageTypes/FGPointDamageType.h"
#include "DamageTypes/FGRadialDamageType.h"

float UWeaponUpgradesBPFL::SetAmmoDamage(UFGAmmoType* ammo, int index, float damage)
{
	//ammo->mMagazineSize = 10000;
	//UFGAmmoType* ammoCDO = Cast<UFGAmmoType>(ammo->GetClass()->GetDefaultObject());
	/*UFGDamageType* damageCDO = Cast<UFGDamageType>(ammo->mDamageTypesOnImpact[index]->GetClass()->GetDefaultObject());
	
	damageCDO->mDamageAmount = damage;*/
	//tempAmmo = ammo;
	ammo->mDamageTypesOnImpact[index]->mDamageAmount = damage;
    
	return ammo->mDamageTypesOnImpact[index]->mDamageAmount;
}

float UWeaponUpgradesBPFL::GetAmmoDamage(UFGAmmoType* ammo, int index)
{
	return ammo->mDamageTypesOnImpact[index]->mDamageAmount;
}

float UWeaponUpgradesBPFL::SetExplosiveDamage(UFGAmmoTypeProjectile* ammo, int index, float damage)
{
	ammo->mDamageTypesAtEndOfLife[index]->mDamageAmount = damage;

	return ammo->mDamageTypesAtEndOfLife[index]->mDamageAmount;
}

float UWeaponUpgradesBPFL::GetExplosiveDamage(UFGAmmoTypeProjectile* ammo, int index)
{
	return ammo->mDamageTypesAtEndOfLife[index]->mDamageAmount;
}

float UWeaponUpgradesBPFL::SetExplosiveRadius(UFGAmmoTypeProjectile* ammo, int index, float cm)
{
	UFGRadialDamageType* damage = Cast< UFGRadialDamageType>(ammo->mDamageTypesAtEndOfLife[index]);

	if (damage == nullptr) return 0;
	damage->mDamageRadius = cm;

	return damage->mDamageRadius;
}

float UWeaponUpgradesBPFL::GetExplosiveRadius(UFGAmmoTypeProjectile* ammo, int index)
{
	UFGRadialDamageType* damage = Cast< UFGRadialDamageType>(ammo->mDamageTypesAtEndOfLife[index]);

	if (damage == nullptr) return 0;
	return damage->mDamageRadius;
}

float UWeaponUpgradesBPFL::SetExplosionRadius(UFGAmmoType* ammo, int index, float cm)
{
	UFGRadialDamageType* damage = Cast<UFGRadialDamageType>(ammo->mDamageTypesOnImpact[index]);

	if (damage == nullptr) return 0;
	damage->mDamageRadius = cm;

	return damage->mDamageRadius;
}

float UWeaponUpgradesBPFL::GetExplosionRadius(UFGAmmoType* ammo, int index)
{
	UFGRadialDamageType* damage = Cast<UFGRadialDamageType>(ammo->mDamageTypesOnImpact[index]);

	if (damage == nullptr) return 0;
	return damage->mDamageRadius;
}

//float UWeaponUpgradesBPFL::SetWeaponReloadTime(UFGEquipmentDescriptor* equip, float seconds)
//{
//	if (equip == nullptr)
//	{
//		UE_LOG(LogWeaponConfigurer, Verbose, TEXT("The weapon loaded is null"));
//	}
//	else
//	{
//		UE_LOG(LogWeaponConfigurer, Verbose, TEXT("Weapon loaded: %s"), *equip->mDisplayName.ToString());
//		AFGWeapon* equipWeapon = Cast<AFGWeapon>(equip->mEquipmentClass);	// ->GetClass()->GetDefaultObject());
//
//		if (equipWeapon == nullptr)
//		{
//			UE_LOG(LogWeaponConfigurer, Verbose, TEXT("The equipment casted is null"));
//		}
//		else
//		{
//			equipWeapon->mReloadTime = seconds;
//
//			return equipWeapon->mReloadTime;
//		}
//	}
//	return 0;
//}

int UWeaponUpgradesBPFL::SetProjectileClusterAmount(AFGProjectile* ammo, int amount)
{
	ammo->mNumClusterProjectiles.Min = amount;
	ammo->mNumClusterProjectiles.Max = amount;
	ammo->mClusterProjectileSpreadIntervalAngle.Min = 260.0 / (float)amount;
	ammo->mClusterProjectileSpreadIntervalAngle.Max = 460.0 / (float)amount;
	ammo->mClusterProjectileSidewaysLaunchSpeed.Min = 0;
	ammo->mClusterProjectileSidewaysLaunchSpeed.Max = 10000;
	ammo->mClusterProjectileVerticalLaunchSpeed.Min = 0;
	ammo->mClusterProjectileVerticalLaunchSpeed.Max = 10000;

	return amount;
}

int UWeaponUpgradesBPFL::GetProjectileClusterAmount(AFGProjectile* ammo)
{
	return ammo->mNumClusterProjectiles.Min;
}

float UWeaponUpgradesBPFL::SetProjectileDamage(AFGProjectile* ammo, int index, float damage)
{
	ammo->mDamageTypesOnImpact[index]->mDamageAmount = damage;

	return ammo->mDamageTypesOnImpact[index]->mDamageAmount;
}

float UWeaponUpgradesBPFL::GetProjectileDamage(AFGProjectile* ammo, int index)
{
	return ammo->mDamageTypesOnImpact[index]->mDamageAmount;
}

float UWeaponUpgradesBPFL::SetDOTDamage(UFGDamageOverTime* dot, float damage)
{
	dot->mDamageTypes[0]->mDamageAmount = damage;

	return dot->mDamageTypes[0]->mDamageAmount;
}

float UWeaponUpgradesBPFL::GetDOTDamage(UFGDamageOverTime* dot)
{
	return dot->mDamageTypes[0]->mDamageAmount;
}

float UWeaponUpgradesBPFL::SetDestructiveRadius(AFGDestructiveProjectile* ammo, float radius)
{
	ammo->mDestructionCollisionComp->SetSphereRadius(radius);

	return ammo->mDestructionCollisionComp->GetUnscaledSphereRadius();
}

float UWeaponUpgradesBPFL::GetDestructiveRadius(AFGDestructiveProjectile* ammo)
{
	return ammo->mDestructionCollisionComp->GetUnscaledSphereRadius();
}

float UWeaponUpgradesBPFL::SetStunSpearDamage(AFGEquipmentStunSpear* ammo, int index, float damage)
{
	ammo->mDamageTypes[index]->mDamageAmount = damage;

	return ammo->mDamageTypes[index]->mDamageAmount;
}

float UWeaponUpgradesBPFL::GetStunSpearDamage(AFGEquipmentStunSpear* ammo, int index)
{
	return ammo->mDamageTypes[index]->mDamageAmount;
}

TArray<UActorComponent*> UWeaponUpgradesBPFL::GetComponents(AActor* actor)
{
	TArray<UActorComponent*> components;
	actor->GetComponents(components, true);
	return components;
}


//UFGDotComponent* UWeaponUpgradesBPFL::MakeFGDotComponent(TSubclassOf<UFGDamageOverTime> dot)
//{
//	UFGDotComponent* comp = new UFGDotComponent();
//
//	comp->mDotClass = dot;
//
//	return comp;
//}