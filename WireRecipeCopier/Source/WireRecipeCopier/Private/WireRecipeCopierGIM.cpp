// Fill out your copyright notice in the Description page of Project Settings.


#include "WireRecipeCopierGIM.h"

UWireRecipeCopierGIM::UWireRecipeCopierGIM()
{
}

UWireRecipeCopierGIM::~UWireRecipeCopierGIM()
{
}

void UWireRecipeCopierGIM::HookAllFactories(UBlueprintSCSHookManager* manager, TSubclassOf<UWireRecipeCopierActorComponent> component)
{
    TArray<FTopLevelAssetPath> nativeRootClassPaths;

    TArray<UClass*> nativeRootClasses;
    GetDerivedClasses(AFGBuildableFactory::StaticClass(), nativeRootClasses);
    nativeRootClasses.Add(AFGBuildableFactory::StaticClass());

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
    //const IAssetRegistry& AssetRegistry = IAssetRegistry::GetChecked();

    for (FTopLevelAssetPath data : allFactories)
    {
        //TArray<FAssetData> AssetData;
        //IAssetRegistry::Get()->GetAssetsByClass(belt.GetAssetName(), AssetData);

        //Filter.ClassPaths.Add(data);
        //UE_LOG(LogAutoBeltTuner, Display, TEXT("Path %s added"), *data.GetAssetName().ToString());
    //}
    //AssetRegistryModule.Get().GetAssets(Filter, AssetData);
        //for (FAssetData data : AssetData)
        //{
        /*if (data.GetAssetName().ToString() != "FGBuildableManufacturer")
        {*/
            UE_LOG(LogWireRecipeCopier, Display, TEXT("Hooking %s ..."), *data.GetAssetName().ToString());

            URootBlueprintSCSHookData* hook = NewObject<URootBlueprintSCSHookData>();
            /*UWireRecipeCopierActorComponent* cdo = Cast<UWireRecipeCopierActorComponent>(component->GetClass()->ClassDefaultObject);
            cdo->Subsystem = Subsystem;
            if (!IsValid(hook))
            {
                UE_LOG(LogWireRecipeCopier, Display, TEXT("Invalid Hook!"));
            }
            else if (hook->ActorClass==nullptr)
            {
                UE_LOG(LogWireRecipeCopier, Display, TEXT("Invalid ActorClass!"));
            }
            else if (FSoftObjectPath(data)==nullptr)
            {
                UE_LOG(LogWireRecipeCopier, Display, TEXT("Invalid Data!"));
            }*/
            hook->ActorClass = FSoftObjectPath(data);
            hook->SetActorComponentClass(component);
            manager->RegisterBlueprintSCSHook(hook);
        //}
        
        
        //}
    }
}
