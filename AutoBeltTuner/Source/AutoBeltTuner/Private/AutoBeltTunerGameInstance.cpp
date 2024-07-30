// Fill out your copyright notice in the Description page of Project Settings.


#include "AutoBeltTunerGameInstance.h"

UAutoBeltTunerGameInstanceModule::UAutoBeltTunerGameInstanceModule()
{
	//HookAllBelts();
}

UAutoBeltTunerGameInstanceModule::~UAutoBeltTunerGameInstanceModule()
{
}

void UAutoBeltTunerGameInstanceModule::HookAllBelts(UBlueprintSCSHookManager* manager,TArray<TSoftClassPtr<AActor>> Belts)
{
    //FAssetRegistryModule& AssetRegistryModule = FModuleManager::LoadModuleChecked<FAssetRegistryModule>("AssetRegistry");
    TArray<FTopLevelAssetPath> nativeRootClassPaths;

    TArray<UClass*> nativeRootClasses;
    GetDerivedClasses(AFGBuildableConveyorBase::StaticClass(), nativeRootClasses);
    nativeRootClasses.Add(AFGBuildableConveyorBase::StaticClass());

    for (const UClass* remoteCallObjectClass : nativeRootClasses)
    {
        if (remoteCallObjectClass != nullptr && remoteCallObjectClass->HasAnyClassFlags(CLASS_Native))
        {
            nativeRootClassPaths.Add(remoteCallObjectClass->GetClassPathName());
        }
    }

    TSet<FTopLevelAssetPath> allBelts;
    IAssetRegistry::Get()->GetDerivedClassNames(nativeRootClassPaths, {}, allBelts);
    allBelts.Append(nativeRootClassPaths);
    //const IAssetRegistry& AssetRegistry = IAssetRegistry::GetChecked();

	for (FTopLevelAssetPath data : allBelts)
	{
        //TArray<FAssetData> AssetData;
        //IAssetRegistry::Get()->GetAssetsByClass(belt.GetAssetName(), AssetData);
        
        //Filter.ClassPaths.Add(data);
        //UE_LOG(LogAutoBeltTuner, Display, TEXT("Path %s added"), *data.GetAssetName().ToString());
	//}
    //AssetRegistryModule.Get().GetAssets(Filter, AssetData);
        //for (FAssetData data : AssetData)
        //{
            UE_LOG(LogAutoBeltTuner, Display, TEXT("Hooking %s ..."), *data.GetAssetName().ToString());

            URootBlueprintSCSHookData* hook = NewObject<URootBlueprintSCSHookData>();
            TSubclassOf<UAutoBeltTunerActorComponent> component = UAutoBeltTunerActorComponent::StaticClass();
            hook->ActorClass = FSoftObjectPath(data);
            hook->SetActorComponentClass(component);
            manager->RegisterBlueprintSCSHook(hook);
        //}
    }
}
