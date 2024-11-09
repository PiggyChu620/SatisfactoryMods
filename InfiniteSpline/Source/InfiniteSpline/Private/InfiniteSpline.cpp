// Copyright Epic Games, Inc. All Rights Reserved.

#include "InfiniteSpline.h"
#

#define LOCTEXT_NAMESPACE "FInfiniteSplineModule"

DEFINE_LOG_CATEGORY(LogInfiniteSpline);

void FInfiniteSplineModule::StartupModule()
{
	if (!WITH_EDITOR)
	{
		AFGBuildableAttachmentSplitter* splitter = GetMutableDefault<AFGBuildableAttachmentSplitter>();
		SUBSCRIBE_METHOD_VIRTUAL_AFTER(AFGBuildableAttachmentSplitter::BeginPlay, splitter, &attachmentHook);

		AFGBuildableAttachmentMerger* merger = GetMutableDefault<AFGBuildableAttachmentMerger>();
		SUBSCRIBE_METHOD_VIRTUAL_AFTER(AFGBuildableAttachmentMerger::BeginPlay, merger, &attachmentHook);

		AFGBuildableSplitterSmart* smart = GetMutableDefault<AFGBuildableSplitterSmart>();
		SUBSCRIBE_METHOD_VIRTUAL_AFTER(AFGBuildableSplitterSmart::BeginPlay, smart, &attachmentHook);

		AFGConveyorBeltHologram* beltHologram = GetMutableDefault<AFGConveyorBeltHologram>();
		SUBSCRIBE_METHOD_VIRTUAL_AFTER(AFGConveyorBeltHologram::BeginPlay, beltHologram, [](AFGConveyorBeltHologram* self)
			{
				AInfiniteSplineModSubsystem* subsystem = AInfiniteSplineModSubsystem::Get(self->GetWorld());

				//UE_LOGFMT(LogInfiniteSpline, Display, "Subsystem: {0}", subsystem->GetName());
				if(IsValid(self) && IsValid(subsystem) && subsystem->BeltEnabled)
				{
					self->mMaxSplineLength = 1000000000000.0;
				}
				/*else
				{
					self->mMaxSplineLength = 5600.100098;
				}*/
			});
		/*SUBSCRIBE_METHOD_VIRTUAL_AFTER(AFGConveyorBeltHologram::CheckValidPlacement, beltHologram, [](AFGConveyorBeltHologram* self)
			{
				if (IsValid(self))
				{
					self->mConstructDisqualifiers.Remove(UFGCDConveyorTooLong::StaticClass());
				}
			});*/
		//SUBSCRIBE_METHOD_VIRTUAL_AFTER(AFGConveyorBeltHologram::ConfigureComponents, beltHologram, [](const AFGConveyorBeltHologram* self, AFGBuildable* inBuildable)
		//	{
		//		if (IsValid(self) && IsValid(inBuildable))
		//		{
		//			AFGBuildableConveyorBelt* belt = Cast<AFGBuildableConveyorBelt>(inBuildable);

		//			if (IsValid(belt))
		//			{
		//				for (FSplinePointData point : belt->mSplineData)
		//				{
		//					UE_LOGFMT(LogInfiniteSpline, Display, "Spline of {0} is {1}", belt->GetName(), point.ToString());
		//				}
		//				
		//			}
		//				//self->mMaxSplineLength = 1000000000000.0;
		//		}
		//	});
		//AFGBuildableConveyorBelt* belt = GetMutableDefault<AFGBuildableConveyorBelt>();
		//SUBSCRIBE_METHOD(AFGBuildableConveyorBelt::Split, [](auto& scope, AFGBuildableConveyorBelt* conveyor, float offset, bool connectNewConveyors)
		//	{
		//		const TArray<AFGBuildableConveyorBelt*>& result = scope(conveyor, offset, true);

		//		for (AFGBuildableConveyorBelt* belt : result)
		//		{
		//			//UE_LOGFMT(LogInfiniteSpline, Display, "== Spline data of {0} ==",belt->GetName());
		//			USplineComponent* comp = belt->GetSplineComponent();
		//			TArray<FVector> newPoints;
		//			//uint8 f = belt->GetConveyorChainFlags();
		//			//UFGFactoryConnectionComponent* c0 = belt->GetConnection0()->GetConnection();
		//			//UFGFactoryConnectionComponent* c1 = belt->GetConnection1()->GetConnection();

		//			//if (IsValid(c0)) UE_LOGFMT(LogInfiniteSpline, Display, "Connection 0: {0}", c0->GetOuterBuildable()->GetName());
		//			//if (IsValid(c1)) UE_LOGFMT(LogInfiniteSpline, Display, "Connection 1: {0}", c1->GetOuterBuildable()->GetName());

		//			for (FSplinePointData data : belt->GetSplinePointData())
		//			{
		//				newPoints.AddUnique(data.Location + FVector(
		//					FMath::FRandRange(-1000.0, 1000.0),
		//					FMath::FRandRange(-1000.0, 1000.0),
		//					FMath::FRandRange(-1000.0, 1000.0)));
		//				//UE_LOGFMT(LogInfiniteSpline, Display, "Adding {0} to the spline", data.Location.ToString());
		//			}
		//			comp->ClearSplinePoints();
		//			for (FVector v : newPoints)
		//			{
		//				comp->AddSplinePoint(v, ESplineCoordinateSpace::Local);
		//			}
		//			for (int i = 0; i < comp->GetNumberOfSplinePoints(); ++i)
		//			{
		//				comp->SetSplinePointType(i, ESplinePointType::Curve);
		//			}
		//			comp->UpdateSpline();
		//			//belt->mSplineData = comp->GetSplineData(ESplineCoordinateSpace::Local);
		//			//belt->UpdateVisibilityMesh();
		//			AFGBuildableConveyorBelt::Respline(belt, comp->GetSplineData(ESplineCoordinateSpace::Local));
		//			//belt->SetConveyorChainFlags(f);
		//			//belt->GetConnection0()->SetConnection(c0);
		//			//belt->GetConnection1()->SetConnection(c1);
		//		}
		//	});
		//SUBSCRIBE_METHOD_AFTER(AFGBuildableConveyorBelt::Split, &splitHook);
		
		AFGPipelineHologram* pipeHologram = GetMutableDefault<AFGPipelineHologram>();
		SUBSCRIBE_METHOD_VIRTUAL_AFTER(AFGPipelineHologram::BeginPlay, pipeHologram, [](AFGPipelineHologram* self)
			{
				AInfiniteSplineModSubsystem* subsystem = AInfiniteSplineModSubsystem::Get(self->GetWorld());
				if (IsValid(self) && IsValid(subsystem) && subsystem->PipeEnabled)
				{
					self->mMaxSplineLength = 1000000000000.0;
				}
				/*else
				{
					self->mMaxSplineLength = 5600.100098;
				}*/
			});

		AFGWireHologram* wireHologram = GetMutableDefault<AFGWireHologram>();
		SUBSCRIBE_METHOD_VIRTUAL_AFTER(AFGWireHologram::BeginPlay, wireHologram, [](AFGWireHologram* self)
			{
				AInfiniteSplineModSubsystem* subsystem = AInfiniteSplineModSubsystem::Get(self->GetWorld());
				if (IsValid(self) && IsValid(subsystem) && subsystem->WireEnabled)
				{
					self->mMaxLength = 1000000000000.0;
					self->mMaxPowerTowerLength = 1000000000000.0;
				}
				/*else
				{
					self->mMaxLength = 10000.0;
					self->mMaxPowerTowerLength = 30000.0;
				}*/
			});

		AFGRailroadTrackHologram* railHologram = GetMutableDefault<AFGRailroadTrackHologram>();
		SUBSCRIBE_METHOD_VIRTUAL_AFTER(AFGRailroadTrackHologram::BeginPlay, railHologram, [](AFGRailroadTrackHologram* self)
			{
				AInfiniteSplineModSubsystem* subsystem = AInfiniteSplineModSubsystem::Get(self->GetWorld());
				if (IsValid(self) && IsValid(subsystem) && subsystem->RailEnabled)
				{
					float maxLength = 1000000000000.0;
					AInfiniteSplineModSubsystem* subsystem = AInfiniteSplineModSubsystem::Get(self->GetWorld());

					if (IsValid(subsystem))
					{
						self->mMaxGrade = subsystem->RailMaxClimb;
						self->mMinBendRadius = subsystem->RailMinBend * 100.0;
						maxLength = subsystem->RailMaxLength * 100000.0;
					}
					self->mMaxLength = maxLength;
				}
				/*else
				{
					self->mMaxGrade = 1500.0;
					self->mMinBendRadius = 25.0;
					self->mMaxLength = 10000.0;
				}*/
			});
		/*SUBSCRIBE_METHOD_VIRTUAL_AFTER(AFGRailroadTrackHologram::CheckValidPlacement, railHologram, [](AFGRailroadTrackHologram* self)
			{
				if (IsValid(self))
				{
					self->mConstructDisqualifiers.Remove(UFGCDTrackTooShort::StaticClass());
				}
			});*/

		AFGConveyorLiftHologram* liftHologram = GetMutableDefault<AFGConveyorLiftHologram>();
		SUBSCRIBE_METHOD_VIRTUAL_AFTER(AFGConveyorLiftHologram::BeginPlay, liftHologram, [](AFGConveyorLiftHologram* self)
			{
				AInfiniteSplineModSubsystem* subsystem = AInfiniteSplineModSubsystem::Get(self->GetWorld());
				if (IsValid(self) && IsValid(subsystem) && subsystem->BeltEnabled)
				{
					self->mMaximumHeight = 1000000000000.0;
				}
			});
	}
}

void FInfiniteSplineModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
}

void FInfiniteSplineModule::splitHook(const TArray<AFGBuildableConveyorBelt*>& result,  AFGBuildableConveyorBelt* conveyor, float offset, bool connectNewConveyors)
{
	/*UE_LOGFMT(LogInfiniteSpline, Display, "== Spline data of the original belt ==");
				for (FSplinePointData data : conveyor->GetSplinePointData())
				{
					UE_LOGFMT(LogInfiniteSpline, Display, "{0}", data.ToString());
				}*/
	//UE_LOGFMT(LogInfiniteSpline, Display, "Connect new conveyors: {0}", connectNewConveyors);
	for (AFGBuildableConveyorBelt* belt : result)
	{
		//UE_LOGFMT(LogInfiniteSpline, Display, "== Spline data of {0} ==",belt->GetName());
		USplineComponent* comp = belt->GetSplineComponent();
		TArray<FVector> newPoints;
		//uint8 f = belt->GetConveyorChainFlags();
		UFGFactoryConnectionComponent* c0 = belt->GetConnection0()->GetConnection();
		UFGFactoryConnectionComponent* c1 = belt->GetConnection1()->GetConnection();

		if(IsValid(c0)) UE_LOGFMT(LogInfiniteSpline, Display, "Connection 0: {0}", c0->GetOuterBuildable()->GetName());
		if(IsValid(c1)) UE_LOGFMT(LogInfiniteSpline, Display, "Connection 1: {0}", c1->GetOuterBuildable()->GetName());

		for (FSplinePointData data : belt->GetSplinePointData())
		{
			newPoints.AddUnique(data.Location+FVector(
				FMath::FRandRange(-1000.0, 1000.0),
				FMath::FRandRange(-1000.0, 1000.0),
				FMath::FRandRange(-1000.0, 1000.0)));
		//UE_LOGFMT(LogInfiniteSpline, Display, "Adding {0} to the spline", data.Location.ToString());
		}
		comp->ClearSplinePoints();
		for (FVector v : newPoints)
		{
			comp->AddSplinePoint(v, ESplineCoordinateSpace::Local);
		}
		for (int i = 0; i < comp->GetNumberOfSplinePoints(); ++i)
		{
			comp->SetSplinePointType(i, ESplinePointType::Curve);
		}
		comp->UpdateSpline();
		//belt->mSplineData = comp->GetSplineData(ESplineCoordinateSpace::Local);
		//belt->UpdateVisibilityMesh();
		//AFGBuildableConveyorBelt::Respline(belt, comp->GetSplineData(ESplineCoordinateSpace::Local));
		//belt->SetConveyorChainFlags(f);
		//belt->GetConnection0()->SetConnection(c0);
		//belt->GetConnection1()->SetConnection(c1);
	}
}

void FInfiniteSplineModule::attachmentHook(AFGBuildableConveyorAttachment* self)
{
	if (IsValid(self))
	{
		AFGBlueprintSubsystem* bpSubsystem = AFGBlueprintSubsystem::Get(self->GetWorld());

		if (IsValid(bpSubsystem))
		{
			/*UE_LOGFMT(LogInfiniteSpline, Display, "== Buildables before repline ==");
			for (AFGBuildable* buildable : bpSubsystem->mBlueprintWorldBuildables)
			{
				UE_LOGFMT(LogInfiniteSpline, Display, "Buildable: {0}", buildable->GetName());
			}*/

			TArray<UFGFactoryConnectionComponent*> connections = self->mInputs;

			connections.Append(self->mOutputs);
			for (UFGFactoryConnectionComponent* comp : connections)
			{
				if (IsValid(comp))
				{
					UFGFactoryConnectionComponent* con = comp->GetConnection();
					if (IsValid(con))
					{
						AFGBuildable* buildable = con->GetOuterBuildable();
						//UE_LOGFMT(LogInfiniteSpline, Display, "Buildable: {0}", buildable->GetName());
						if (IsValid(buildable) && buildable->IsA<AFGBuildableConveyorBelt>())
						{
							AFGBuildableConveyorBelt* belt = Cast<AFGBuildableConveyorBelt>(buildable);
							//UE_LOGFMT(LogInfiniteSpline, Display, "Belt: {0}", belt->GetName());
							USplineComponent* comp = belt->GetSplineComponent();
							TArray<FVector> newPoints;
							//uint8 f = belt->GetConveyorChainFlags();
							//UFGFactoryConnectionComponent* c0 = belt->GetConnection0()->GetConnection();
							//UFGFactoryConnectionComponent* c1 = belt->GetConnection1()->GetConnection();

							//if (IsValid(c0)) UE_LOGFMT(LogInfiniteSpline, Display, "Connection 0: {0}", c0->GetOuterBuildable()->GetName());
							//if (IsValid(c1)) UE_LOGFMT(LogInfiniteSpline, Display, "Connection 1: {0}", c1->GetOuterBuildable()->GetName());

							for (FSplinePointData data : belt->GetSplinePointData())
							{
								newPoints.AddUnique(data.Location);	// +FVector(
								//FMath::FRandRange(-1000.0, 1000.0),
								//FMath::FRandRange(-1000.0, 1000.0),
								//FMath::FRandRange(-1000.0, 1000.0)));
							//UE_LOGFMT(LogInfiniteSpline, Display, "Adding {0} to the spline", data.Location.ToString());
							}
							Algo::Sort(newPoints, [](const FVector& a, const FVector& b)
								{
									return a.SizeSquared() < b.SizeSquared();
								});
							comp->ClearSplinePoints();
							for (FVector v : newPoints)
							{
								comp->AddSplinePoint(v, ESplineCoordinateSpace::Local);
							}
							for (int i = 0; i < comp->GetNumberOfSplinePoints(); ++i)
							{
								comp->SetSplinePointType(i, ESplinePointType::Curve);
							}
							comp->UpdateSpline();
							AFGBuildableConveyorBelt::Respline(belt, comp->GetSplineData(ESplineCoordinateSpace::Local));
							//int i = 0;
							//for (AFGBuildableBlueprintDesigner* blueprint : bpSubsystem->mAllBlueprintDesigners)
							//{
							//	if (blueprint->mBuildables.Num() > 0)
							//	{
							//		UE_LOGFMT(LogInfiniteSpline, Display, "Blueprint {0}:", i++);
							//		for (AFGBuildable* buildable : blueprint->mBuildables)
							//		{
							//			UE_LOGFMT(LogInfiniteSpline, Display, "Buildable: {0}", buildable->GetName());
							//		}
							//	}
							//	//blueprint->OnBuildingsChanged();
							//}
							break;
						}
					}

				}
			}
			/*UE_LOGFMT(LogInfiniteSpline, Display, "== Buildables after repline ==");
			for (AFGBuildable* buildable : bpSubsystem->mBlueprintWorldBuildables)
			{
				UE_LOGFMT(LogInfiniteSpline, Display, "Buildable: {0}", buildable->GetName());
			}*/
		}
		
	}
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FInfiniteSplineModule, InfiniteSpline)