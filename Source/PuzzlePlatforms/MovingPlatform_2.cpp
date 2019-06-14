// Fill out your copyright notice in the Description page of Project Settings.

#include "MovingPlatform_2.h"


FTarget* AMovingPlatform_2::Begin() { return Locations.GetData(); }
FTarget* AMovingPlatform_2::End() { return Locations.GetData() + Locations.Num(); }
const FTarget* AMovingPlatform_2::cBegin() const { return Locations.GetData(); }
const FTarget* AMovingPlatform_2::cEnd() const { return Locations.GetData() + Locations.Num(); }

AMovingPlatform_2::AMovingPlatform_2()
{
	SetMobility(EComponentMobility::Movable);
	PrimaryActorTick.bCanEverTick = true;
	bReplicateMovement = true;
	FString;
	bReplicates = true;
	RotateOption = FFinishedOption::Cycle;
}

void AMovingPlatform_2::BeginPlay()
{
	Super::BeginPlay();
	if (!bLoop)
	{
		RotateOption = FFinishedOption::Cycle;
	}
	if (Curve && Locations.Num() && HasAuthority())
	{
		for (auto&& Target : Locations)
		{
			Target.Location = GetTransform().TransformPosition(Target.Location);
		}
		//Add the initial location to the front of the array
		Locations.EmplaceAt(0, FTarget(GetActorLocation(), Time));
		InitialLocation = GetActorLocation();

		//set the first target
		TargetInfo = &Locations[1];

		FOnTimelineFloat ProgFunc;
		ProgFunc.BindUFunction(this, TEXT("MovePlatform"));
		MoveTimeline.AddInterpFloat(Curve, ProgFunc);
		MoveTimeline.SetPlayRate(1 / TargetInfo->Time);

		FOnTimelineEvent OnFinish;
		OnFinish.BindUFunction(this, TEXT("NextTarget"));
		MoveTimeline.SetTimelineFinishedFunc(OnFinish);
		if (bStartActivated)
		{
			MoveTimeline.PlayFromStart();
		}
	}
}

void AMovingPlatform_2::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	MoveTimeline.TickTimeline(DeltaTime);
}

void AMovingPlatform_2::MovePlatform(float Delta)
{
	const FVector TargetDelta = TargetInfo->Location;
	const float TargetTime = TargetInfo->Time;
	MoveTimeline.SetPlayRate(1 / TargetTime);
	FVector Location = FMath::Lerp(InitialLocation, TargetDelta, Delta);
	SetActorLocation(Location);
}

void AMovingPlatform_2::NextTarget()
{
	InitialLocation = GetActorLocation();
	switch (RotateOption)
	{
	case FFinishedOption::Cycle:
		//iterate the array
		if (TargetInfo++ != cEnd() - 1)
		{
			MoveTimeline.PlayFromStart();
			return;
		}
		//if end of array set the next location to the starting location
		if (bLoop)
		{
			TargetInfo = Begin();
			MoveTimeline.PlayFromStart();
			return;
		}
		break;
	case FFinishedOption::Reverse:
		//forwards
		if (!bReverse)
		{
			if (++TargetInfo != cEnd())
			{
				MoveTimeline.PlayFromStart();
				return;
			}
			//iterate back to Begin
			--TargetInfo;
			bReverse = true;
		}
		if (bReverse)
		{
			if (TargetInfo-- != cBegin())
			{
				MoveTimeline.PlayFromStart();
				return;
			}
			bReverse = false;
			//reset to first target
			TargetInfo = &Locations[1];
			MoveTimeline.PlayFromStart();
		}
		break;
	}
}

void AMovingPlatform_2::Start()
{
	MoveTimeline.Play();
}

void AMovingPlatform_2::Stop()
{
	MoveTimeline.Stop();
}


