// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"
#include <Logging/StructuredLog.h>

DECLARE_LOG_CATEGORY_EXTERN(LogSatisFactorio, Display, All);

class FSatisFactorioModule : public IModuleInterface
{
public:

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
};
