// Fill out your copyright notice in the Description page of Project Settings.

#include "MovingPlatform.h"


AMovingPlatform::AMovingPlatform()
{
	PrimaryActorTick.bCanEverTick = true;

	SetMobility(EComponentMobility::Movable);
}

void AMovingPlatform::AddActiveTrigger()
{
	ActiveTriggers++;
}

void AMovingPlatform::RemoveActiveTrigger()
{
	if (ActiveTriggers > 0)
	{
		ActiveTriggers--;
	}
}

void AMovingPlatform::BeginPlay()
{
	Super::BeginPlay();

	if (HasAuthority())
	{
		SetReplicates(true);
		SetReplicateMovement(true);
	}

	GlobalStartLocation = GetActorLocation();
	GlobalTargetLocation = GetTransform().TransformPosition(TargetLocation);
}

void AMovingPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (ActiveTriggers > 0)
	{
		if (HasAuthority())   // !HasAuthority() = Not Server
		{
			auto Location = GetActorLocation();

			float DestinationLength = (GlobalTargetLocation - GlobalStartLocation).Size();
			float BoxTraveLength = (Location - GlobalStartLocation).Size();

			if (BoxTraveLength >= DestinationLength)
			{
				auto Swap = GlobalTargetLocation;
				GlobalTargetLocation = GlobalStartLocation;
				GlobalStartLocation = Swap;
				return;
			}

			auto Diretion = (GlobalTargetLocation - GlobalStartLocation).GetSafeNormal();  // Get size=1 (Unit) Vector in relevant direction

			auto UpdateLocation = (Diretion * DeltaTime * Speed) + Location;
			//Location += FVector(Speed * DeltaTime * Diretion, 0, 0);
			SetActorLocation(UpdateLocation);
		}

	}


}