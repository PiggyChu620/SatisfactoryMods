// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponUpgradesSubsystem.h"
#include <UnrealNetwork.h>

AWeaponUpgradesSubsystem::AWeaponUpgradesSubsystem()
{
	bReplicates = true;
}

AWeaponUpgradesSubsystem::~AWeaponUpgradesSubsystem()
{
}

void AWeaponUpgradesSubsystem::BeginPlay()
{
	Super::BeginPlay();

	GetAllAmmo();
	Init();
}

bool AWeaponUpgradesSubsystem::isExplosive(const UFGDamageType* damage)
{
	return damage->IsA<UFGRadialDamageType>();
}

bool AWeaponUpgradesSubsystem::isPointDamage(const UFGDamageType* damage)
{
	return damage->IsA<UFGPointDamageType>();
}

bool AWeaponUpgradesSubsystem::isRifleAmmo(const UFGAmmoType* ammo)
{
	for (FCompatibleItemDescriptors com : ammo->mCompatibleItemDescriptors)
	{
		for (TSubclassOf<UFGItemDescriptor> item : com.CompatibleItemDescriptors)
		{
			if (item == Rifle) return true;
		}
	}
	return false;
}

bool AWeaponUpgradesSubsystem::isRebarAmmo(const UFGAmmoType* ammo)
{
	for (FCompatibleItemDescriptors com : ammo->mCompatibleItemDescriptors)
	{
		for (TSubclassOf<UFGItemDescriptor> item : com.CompatibleItemDescriptors)
		{
			if (item == RebarGun) return true;
		}
	}
	return false;
}

double AWeaponUpgradesSubsystem::getTotalExplosiveDamage(const UFGAmmoType* ammo)
{
	double sum = 0.0;
	const UFGAmmoTypeProjectile* projectile = Cast<UFGAmmoTypeProjectile>(ammo);

	if (IsValid(projectile))
	{
		for (UFGDamageType* damage : projectile->mDamageTypesAtEndOfLife)
		{
			if (damage->IsA<UFGRadialDamageType>())
			{
				sum += damage->mDamageAmount;
			}
		}
	}
	for (UFGDamageType* damage : ammo->mDamageTypesOnImpact)
	{
		if (damage->IsA<UFGRadialDamageType>())
		{
			sum += damage->mDamageAmount;
		}
	}

	return sum;
}

double AWeaponUpgradesSubsystem::getTotalExplosiveRadius(const UFGAmmoType* ammo)
{
	double sum = 0.0;
	const UFGAmmoTypeProjectile* projectile = Cast<UFGAmmoTypeProjectile>(ammo);

	if (IsValid(projectile))
	{
		for (UFGDamageType* damage : projectile->mDamageTypesAtEndOfLife)
		{
			if (damage->IsA<UFGRadialDamageType>())
			{
				UFGRadialDamageType* radial = Cast<UFGRadialDamageType>(damage);

				sum += radial->mDamageRadius;
			}
		}
	}
	for (UFGDamageType* damage : ammo->mDamageTypesOnImpact)
	{
		if (damage->IsA<UFGRadialDamageType>())
		{
			UFGRadialDamageType* radial = Cast<UFGRadialDamageType>(damage);

			sum += radial->mDamageRadius;
		}
	}

	return sum;
}

double AWeaponUpgradesSubsystem::getTotalPointDamage(const UFGAmmoType* ammo)
{
	double sum = 0.0;
	const UFGAmmoTypeProjectile* projectile = Cast<UFGAmmoTypeProjectile>(ammo);

	if (IsValid(projectile))
	{
		for (UFGDamageType* damage : projectile->mDamageTypesAtEndOfLife)
		{
			if (damage->IsA<UFGPointDamageType>())
			{
				sum += damage->mDamageAmount;
			}
		}
	}
	for (UFGDamageType* damage : ammo->mDamageTypesOnImpact)
	{
		if (damage->IsA<UFGPointDamageType>())
		{
			sum += damage->mDamageAmount;
		}
	}

	return sum;
}

void AWeaponUpgradesSubsystem::setExplosiveDamage(UFGAmmoType* ammo, double damage)
{
	bool set=false;
	UFGAmmoTypeProjectile* projectile = Cast<UFGAmmoTypeProjectile>(ammo);

	if (IsValid(projectile))
	{
		UFGDamageType** d = projectile->mDamageTypesAtEndOfLife.FindByPredicate(isExplosive);

		if (d && (*d)->IsA<UFGRadialDamageType>())
		{
			projectile->mDamageTypesAtEndOfLife.Empty();
			(*d)->mDamageAmount = damage;
			projectile->mDamageTypesAtEndOfLife.Emplace(*d);
			set = true;
		}
	}
	if (!set)
	{
		UFGDamageType** d = ammo->mDamageTypesOnImpact.FindByPredicate(isExplosive);

		if (d && (*d)->IsA<UFGRadialDamageType>())
		{
			ammo->mDamageTypesOnImpact.Empty();
			(*d)->mDamageAmount = damage;
			ammo->mDamageTypesOnImpact.Emplace(*d);
		}
	}
}

void AWeaponUpgradesSubsystem::setExplosiveRadius(UFGAmmoType* ammo, double radius)
{
	bool set = false;
	UFGAmmoTypeProjectile* projectile = Cast<UFGAmmoTypeProjectile>(ammo);

	if (IsValid(projectile))
	{
		UFGDamageType** d = projectile->mDamageTypesAtEndOfLife.FindByPredicate(isExplosive);

		if (d && (*d)->IsA<UFGRadialDamageType>())
		{
			UFGRadialDamageType* radial = Cast<UFGRadialDamageType>(*d);

			projectile->mDamageTypesAtEndOfLife.Empty();
			radial->mDamageRadius = radius;
			projectile->mDamageTypesAtEndOfLife.Emplace(radial);
			set = true;
		}
	}
	if (!set)
	{
		UFGDamageType** d = ammo->mDamageTypesOnImpact.FindByPredicate(isExplosive);

		if (d && (*d)->IsA<UFGRadialDamageType>())
		{
			UFGRadialDamageType* radial = Cast<UFGRadialDamageType>(*d);

			ammo->mDamageTypesOnImpact.Empty();
			radial->mDamageRadius = radius * ExplosionRadiusMultiplier;
			ammo->mDamageTypesOnImpact.Emplace(radial);
		}
	}
}

void AWeaponUpgradesSubsystem::setPointDamage(UFGAmmoType* ammo, double damage)
{
	bool set = false;
	UFGAmmoTypeProjectile* projectile = Cast<UFGAmmoTypeProjectile>(ammo);

	if (IsValid(projectile))
	{
		UFGDamageType** d = projectile->mDamageTypesAtEndOfLife.FindByPredicate(isPointDamage);

		if (d && (*d)->IsA<UFGPointDamageType>())
		{
			projectile->mDamageTypesAtEndOfLife.Empty();
			(*d)->mDamageAmount = damage;
			projectile->mDamageTypesAtEndOfLife.Emplace(*d);
			set = true;
		}
	}
	if (!set)
	{
		UFGDamageType** d = ammo->mDamageTypesOnImpact.FindByPredicate(isPointDamage);

		if (d && (*d)->IsA<UFGPointDamageType>())
		{
			ammo->mDamageTypesOnImpact.Empty();
			(*d)->mDamageAmount = damage;
			ammo->mDamageTypesOnImpact.Emplace(*d);
		}
	}
}

void AWeaponUpgradesSubsystem::setShatterAmount(UFGAmmoType* ammo, double amount)
{
	UFGAmmoTypeProjectile* projectile = Cast<UFGAmmoTypeProjectile>(ammo);

	if (IsValid(projectile))
	{
		TSubclassOf<AFGProjectile> cluster = projectile->GetProjectileClass();

		if (IsValid(cluster))
		{
			AFGProjectile* clusterCDO = cluster.GetDefaultObject();

			clusterCDO->mNumClusterProjectiles.Min = amount;
			clusterCDO->mNumClusterProjectiles.Max = amount;
		}
	}
	else
	{
		UFGAmmoTypeSpreadshot* spreadshot = Cast<UFGAmmoTypeSpreadshot>(ammo);

		if (IsValid(spreadshot))
		{
			spreadshot->mNumShots.Min = amount;
			spreadshot->mNumShots.Max = amount;
		}
	}
}

double AWeaponUpgradesSubsystem::getShematicLevel(const TArray<TSubclassOf<UFGSchematic>>& schematic)
{
	for (int i = 9; i >= 0; i--)
	{
		if (SchematicManager->IsSchematicPurchased(schematic[i])) return i + 1.0;
	}
	return 0;
}


double AWeaponUpgradesSubsystem::GetMultiplier(double level)
{
	if (IsExponentialProgression)
	{
		return FMath::Pow(1.0 + BaseValue / 100.0, level);
	}
	else
	{
		return 1.0 + level * BaseValue / 100.0;
	}
}

void AWeaponUpgradesSubsystem::SetAllDamages_Server()
{
	double multiplier = GetMultiplier(getShematicLevel(DamageSchematics));

	UpgradedDamages.Empty();
	for (TPair<UFGAmmoType*, double> pair : BaseDamages)
	{
		UpgradedDamages.Emplace(FAmmoUpgrade(pair.Key, pair.Value * multiplier));
	}
}

void AWeaponUpgradesSubsystem::SetAllDamages()
{
	for (FAmmoUpgrade ammo:UpgradedDamages)
	{
		setPointDamage(ammo.Ammo,ammo.Value);
	}
}

void AWeaponUpgradesSubsystem::SetAllFireRates_Server()
{
	double multiplier = GetMultiplier(getShematicLevel(FireRateSchematics));

	UpgradedFireRates.Empty();
	for (TPair<UFGAmmoType*, double> pair : BaseFireRates)
	{
		UpgradedFireRates.Emplace(FAmmoUpgrade(pair.Key, pair.Value * multiplier));
	}
}

void AWeaponUpgradesSubsystem::SetAllFireRates()
{
	for (FAmmoUpgrade upgrade : UpgradedFireRates)
	{
		upgrade.Ammo->mFireRate = upgrade.Value;
	}
}

void AWeaponUpgradesSubsystem::SetAllSizes_Server()
{
	double multiplier = GetMultiplier(getShematicLevel(SizeSchematics));

	UpgradedSizes.Empty();
	for (TPair<UFGAmmoType*, double> pair : BaseSizes)
	{
		double baseMultiplier = 1.0;

		if (isRebarAmmo(pair.Key)) baseMultiplier = RebarMagazineMultiplier;
		UpgradedSizes.Emplace(FAmmoUpgrade(pair.Key, pair.Value * multiplier * baseMultiplier));
	}
}

void AWeaponUpgradesSubsystem::SetAllSizes()
{
	for(FAmmoUpgrade upgrade:UpgradedSizes)
	{
		upgrade.Ammo->mMagazineSize = upgrade.Value;
		if (upgrade.Ammo->mMagazineSize < 1) upgrade.Ammo->mMagazineSize = 1;
	}
}

void AWeaponUpgradesSubsystem::SetAllExplosiveDamages_Server()
{
	double multiplier = GetMultiplier(getShematicLevel(ExplosionDamageSchematics));

	UpgradedExposionDamages.Empty();
	for (TPair<UFGAmmoType*, double> pair : BaseExplotionDamages)
	{
		UpgradedExposionDamages.Emplace(FAmmoUpgrade(pair.Key, pair.Value * multiplier));
	}
}

void AWeaponUpgradesSubsystem::SetAllExplosiveDamages()
{
	for(FAmmoUpgrade upgrade: UpgradedExposionDamages)
	{
		setExplosiveDamage(upgrade.Ammo,upgrade.Value);
	}
}

void AWeaponUpgradesSubsystem::SetAllExplosiveRadius_Server()
{
	double multiplier = GetMultiplier(getShematicLevel(ExplosionRadiusSchematics));

	UpgradedExposionRadiuses.Empty();
	for (TPair<UFGAmmoType*, double> pair : BaseRadiuses)
	{
		UpgradedExposionRadiuses.Emplace(FAmmoUpgrade(pair.Key, pair.Value * multiplier * ExplosionRadiusMultiplier));
	}
}

void AWeaponUpgradesSubsystem::SetAllExplosiveRadius()
{
	for(FAmmoUpgrade upgrade: UpgradedExposionRadiuses)
	{
		setExplosiveRadius(upgrade.Ammo,upgrade.Value);
	}
}

void AWeaponUpgradesSubsystem::SetAllShatterAmounts_Server()
{
	double multiplier = GetMultiplier(getShematicLevel(ShatterAmountSchematics));

	UpgradedShatterAmounts.Empty();
	for (TPair<UFGAmmoType*, double> pair : BaseShatterAmounts)
	{
		UpgradedShatterAmounts.Emplace(pair.Key, pair.Value * multiplier);
	}
}

void AWeaponUpgradesSubsystem::SetAllShatterAmounts()
{
	for(FAmmoUpgrade upgrade: UpgradedShatterAmounts)
	{
		setShatterAmount(upgrade.Ammo, upgrade.Value);
	}
}

void AWeaponUpgradesSubsystem::Init()
{
	//if (!IsBaseValueSet)
	//{
		USessionSettingsManager* sessionSettings = GetWorld()->GetSubsystem<USessionSettingsManager>();

		for (UFGAmmoType* ammo : Ammos)
		{
			bool isStunAmmo = false;
			UFGAmmoTypeProjectile* projectile = Cast<UFGAmmoTypeProjectile>(ammo);

			if (IsValid(projectile))
			{
				TSubclassOf<AFGProjectile> cluster = projectile->GetProjectileClass();
				if (IsValid(cluster))
				{
					AFGProjectile* clusterCDO = cluster.GetDefaultObject();

					if (clusterCDO == BP_Rebar_Stunshot)
					{
						BaseStunDurations.Emplace(ammo, GetStunDuration());
						isStunAmmo = true;
					}
					else
					{
						BaseShatterAmounts.Emplace(ammo, clusterCDO->mNumClusterProjectiles.Max);
						TSubclassOf<AFGProjectile> clusterProjectile = clusterCDO->mClusterProjectileClass;
						if (IsValid(clusterProjectile))
						{
							AFGProjectile* clusterProjectileCDO = clusterProjectile.GetDefaultObject();
							BaseDamages.Emplace(ammo, clusterProjectileCDO->mDamageTypesOnImpact[0]->mDamageAmount);
						}
					}
				}
			}
			if (!isStunAmmo)
			{
				double damage = getTotalExplosiveDamage(ammo);

				if (damage > 0.0)
				{
					BaseExplotionDamages.Emplace(ammo, damage);
					BaseRadiuses.Emplace(ammo, getTotalExplosiveRadius(ammo));
				}
				else
				{
					damage = getTotalPointDamage(ammo);
					if (damage > 0.0)
					{
						BaseDamages.Emplace(ammo, damage);
					}
				}
			}

			if (ammo->IsA<UFGAmmoTypeSpreadshot>())
			{
				UFGAmmoTypeSpreadshot* shot = Cast<UFGAmmoTypeSpreadshot>(ammo);

				if (IsValid(shot))
				{
					BaseShatterAmounts.Emplace(ammo, shot->mNumShots.Max);
				}
			}
			BaseSizes.Emplace(ammo, ammo->mMagazineSize);
			BaseFireRates.Emplace(ammo, ammo->mFireRate);
		}
	//}
	
}

void AWeaponUpgradesSubsystem::GetAllAmmo()
{
	TArray<UClass*> nativeRootClasses;
	TArray<FTopLevelAssetPath> nativeRootClassPaths;
	GetDerivedClasses(UFGAmmoType::StaticClass(), nativeRootClasses);
	nativeRootClasses.Add(UFGAmmoType::StaticClass());

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
		UE_LOGFMT(LogWeaponUpgrades, Display, "Checking {0}", *data.GetAssetName().ToString());
		TSubclassOf<UFGAmmoType> ammo = TSoftClassPtr<UFGAmmoType>(FSoftObjectPath(data)).Get();
		UFGAmmoType* cdo = ammo.GetDefaultObject();
		if (IsValid(ammo) && IsValid(cdo))
		{
			Ammos.Emplace(cdo);
			//UE_LOGFMT(LogWeaponUpgrades, Display, "{0} added to the array", cdo->mDisplayName);
		}
	}
}

void AWeaponUpgradesSubsystem::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AWeaponUpgradesSubsystem, UpgradedDamages);
	DOREPLIFETIME(AWeaponUpgradesSubsystem, UpgradedFireRates);
	DOREPLIFETIME(AWeaponUpgradesSubsystem, UpgradedSizes);
	DOREPLIFETIME(AWeaponUpgradesSubsystem, UpgradedExposionDamages);
	DOREPLIFETIME(AWeaponUpgradesSubsystem, UpgradedExposionRadiuses);
	DOREPLIFETIME(AWeaponUpgradesSubsystem, UpgradedShatterAmounts);
}

