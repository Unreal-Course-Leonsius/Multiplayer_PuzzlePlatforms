// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/StaticMeshActor.h"
#include "MovingPlatform.generated.h"


/*USTRUCT()
struct FTarget
{
	GENERATED_BODY()
	FTarget() : Location(FVector::ZeroVector), Time(1.f) {}
	FTarget(FVector Vec, float T) : Location(Vec), Time(T) {}

	UPROPERTY(EditAnywhere, meta = (MakeEditWidget = true))
	FVector Location;
	UPROPERTY(EditAnywhere, meta = (ClampMin = 0.5, UIMin = 0.5))
	float Time;
};*/


/**
 * 
 */
UCLASS()
class PUZZLEPLATFORMS_API AMovingPlatform : public AStaticMeshActor
{
	GENERATED_BODY()
	
public:

	AMovingPlatform();

	// it's for PlatformTrigger
	void AddActiveTrigger();
	void RemoveActiveTrigger();

protected:

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;


protected:

	UPROPERTY(EditAnywhere)
	float Speed = 10.f;

	UPROPERTY(EditAnywhere, Meta = (MakeEditWidget = true))
	FVector TargetLocation;
	
private:

	FVector GlobalStartLocation;
	FVector GlobalTargetLocation;

	UPROPERTY(EditAnywhere)
	int32 ActiveTriggers = 1;
	
};
