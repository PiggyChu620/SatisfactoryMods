// Fill out your copyright notice in the Description page of Project Settings.


#include "SatisFactorioSubsystem.h"

ASatisFactorioSubsystem::ASatisFactorioSubsystem()
{
    CallbackHandler = MakeShared<FAssetLoadHandler>();
}

ASatisFactorioSubsystem::~ASatisFactorioSubsystem()
{
}

TArray<TSubclassOf<UFGItemDescriptor>> ASatisFactorioSubsystem::GetAllFuels()
{
    return CallbackHandler->AllFuels;
}

void ASatisFactorioSubsystem::BeginPlay()
{
	Super::BeginPlay();

	/*if (AllFuels.IsEmpty())
	{
		TArray<UObject*> items;
		GetObjectsOfClass(UFGItemDescriptor::StaticClass(), items, true, EObjectFlags::RF_FinishDestroyed);
		for (UObject* i : items)
		{
			UE_LOGFMT(LogSatisFactorio, Display, "Checking {0}", i->GetName());
			UFGItemDescriptor* item = Cast<UFGItemDescriptor>(i);

			if (IsValid(item) && UFGItemDescriptor::GetEnergyValue(item->GetClass()) > 0)
			{
				AllFuels.AddUnique(item->GetClass());
				UE_LOGFMT(LogSatisFactorio, Display, "{0} added to the array", item->GetName());
			}
		}
	}*/
    FStreamableManager& Streamable = UAssetManager::GetStreamableManager();
    TArray<FTopLevelAssetPath> nativeRootClassPaths;
    TWeakPtr<FAssetLoadHandler> WeakCallbackHandler = CallbackHandler;

    TArray<UClass*> nativeRootClasses;
    GetDerivedClasses(UFGItemDescriptor::StaticClass(), nativeRootClasses);
    nativeRootClasses.Add(UFGItemDescriptor::StaticClass());

    for (const UClass* remoteCallObjectClass : nativeRootClasses)
    {
        if (remoteCallObjectClass != nullptr && remoteCallObjectClass->HasAnyClassFlags(CLASS_Native))
        {
            nativeRootClassPaths.Add(remoteCallObjectClass->GetClassPathName());
        }
    }

    TSet<FTopLevelAssetPath> allFactories;
    IAssetRegistry::Get()->GetDerivedClassNames(nativeRootClassPaths, {}, allFactories);
    allFactories.Append(nativeRootClassPaths);
    for (FTopLevelAssetPath data : allFactories)
    {
        const FSoftObjectPath path = FSoftObjectPath(data);
        UObject* obj = path.ResolveObject();


        if(IsValid(obj))
        {
            UE_LOGFMT(LogSatisFactorio, Display, "Processing {0}", obj->GetName());
            CallbackHandler->OnAssetLoaded(path);
        }
        else
        {
            UE_LOGFMT(LogSatisFactorio, Display, "Requesting Async Load for {0}", obj->GetName());
            Streamable.RequestAsyncLoad(path, FStreamableDelegate::CreateLambda([WeakCallbackHandler, path]()
                {
                    if (TSharedPtr<FAssetLoadHandler> PinnedCallbackHandler = WeakCallbackHandler.Pin())
                    {
                        PinnedCallbackHandler->OnAssetLoaded(path);
                    }
                }));
        }
    }
}
