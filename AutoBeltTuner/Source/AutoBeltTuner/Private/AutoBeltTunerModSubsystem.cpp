// Fill out your copyright notice in the Description page of Project Settings.


#include "AutoBeltTunerModSubsystem.h"


AAutoBeltTunerModSubsystem::AAutoBeltTunerModSubsystem()
{
	//PrimaryActorTick.bCanEverTick=true;
}

AAutoBeltTunerModSubsystem::~AAutoBeltTunerModSubsystem()
{
}

void AAutoBeltTunerModSubsystem::SetBeltSpeed_Implementation(AFGBuildableConveyorBase* belt, float speed)
{
	FScopeTryLock ScopeLock(&CriticalSection);

	if (ScopeLock.IsLocked())
	{
		if (IsValid(belt) && belt->mSpeed != speed)
		{
			belt->mSpeed = speed;
			/*TSharedPtr<TMpscQueue<float>> queue = speedQueues.FindOrAdd(belt);
			if (queue == nullptr) queue = MakeShared<TMpscQueue<float>>();
			queue->Enqueue(speed);*/
			/*AsyncTask(ENamedThreads::AnyBackgroundHiPriTask, [belt,speed]
				{
					if (belt->mSpeed != speed) belt->mSpeed = speed;
				});*/
		}
	}
	
}

void AAutoBeltTunerModSubsystem::BeginPlay()
{
	Super::BeginPlay();
	
	/*for (TActorIterator<AFGBuildableConveyorBase> It(GetWorld(), AFGBuildableConveyorBase::StaticClass(), EActorIteratorFlags::AllActors); It; ++It)
	{
		AFGBuildableConveyorBase* belt = *It;
		UE_LOG(LogAutoBeltTuner, Display, TEXT("Belt: %s"), *belt->GetFName().ToString())
	}*/
}
//
//void AAutoBeltTunerModSubsystem::Tick(float ds)
//{
//	Super::Tick(ds);
//
//	//AsyncTask(ENamedThreads::AnyBackgroundHiPriTask, [this]
//	//	{
//	//		//while (true)
//	//		//{
//	//			/*TArray<AFGBuildableConveyorBase*> belts;
//	//			speedQueues.GetKeys(belts);
//	//			for (AFGBuildableConveyorBase* belt : belts)
//	//			{
//	//				float speed;
//	//				if (speedQueues[belt].Dequeue(speed) && belt->mSpeed!=speed)
//	//				{
//	//					belt->mSpeed = speed;
//	//				}
//	//			}*/
//	//		//UE_LOG(LogAutoBeltTuner, Display, TEXT("Subsystem Tick running..."));
//	//		if (!running)
//	//		{
//	//			running = true;
//	//			for (TPair<AFGBuildableConveyorBase*, TSharedPtr<TMpscQueue<float>>> kv : speedQueues)
//	//			{
//	//				float speed;
//	//				UE_LOG(LogAutoBeltTuner, Display, TEXT("Is Queue Valid: %s"), kv.Value.IsValid());
//	//				if (kv.Value.IsValid() && kv.Value->Dequeue(speed) && kv.Key->mSpeed != speed)
//	//				{
//	//					kv.Key->mSpeed = speed;
//	//				}
//	//			}
//	//			running = false;
//	//		}
//	//			
//	//		//}
//	//	});
//}

