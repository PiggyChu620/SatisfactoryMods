// Copyright Epic Games, Inc. All Rights Reserved.

#include "WeaponUpgrades.h"

#define LOCTEXT_NAMESPACE "FWeaponUpgradesModule"

DEFINE_LOG_CATEGORY(LogWeaponUpgrades);

void FWeaponUpgradesModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
}

void FWeaponUpgradesModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FWeaponUpgradesModule, WeaponUpgrades)