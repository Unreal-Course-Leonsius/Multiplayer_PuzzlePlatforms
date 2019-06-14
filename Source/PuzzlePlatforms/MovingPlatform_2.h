// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/StaticMeshActor.h"
#include "Components/TimelineComponent.h"
#include "MovingPlatform_2.generated.h"

USTRUCT()
struct FTarget
{
	GENERATED_BODY()
		FTarget() : Location(FVector::ZeroVector), Time(1.f) {}
	FTarget(FVector Vec, float T) : Location(Vec), Time(T) {}

	UPROPERTY(EditAnywhere, meta = (MakeEditWidget = true))
		FVector Location;
	UPROPERTY(EditAnywhere, meta = (ClampMin = 0.5, UIMin = 0.5))
		float Time;
};

UENUM(BlueprintType)
enum class FFinishedOption : uint8
{
	Cycle	UMETA(DisplayName = "Cycle"),
	Reverse UMETA(DisplayNamew = "Reverse")
};


/**
 * 
 */
UCLASS()
class PUZZLEPLATFORMS_API AMovingPlatform_2 : public AStaticMeshActor
{
	GENERATED_BODY()
	
public:
	AMovingPlatform_2();
	UFUNCTION(BlueprintCallable)
		void Start();
	UFUNCTION(BlueprintCallable)
		void Stop();
protected:

	virtual	void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	inline FTarget* Begin();
	inline FTarget* End();
	inline const FTarget* cBegin() const;
	inline const FTarget* cEnd() const;

	UFUNCTION()
		void MovePlatform(float Delta);

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool bStartActivated;
private:
	UPROPERTY(EditDefaultsOnly)
		class UCurveFloat* Curve;

	UPROPERTY(EditAnywhere)
		bool bLoop = true;

	UPROPERTY(EditAnywhere, meta = (EditCondition = bLoop))
		FFinishedOption RotateOption;

	UPROPERTY(EditAnywhere, meta = (ClampMin = 0.5, UIMin = 0.5))
		float Time = 1.f;

	FTimeline MoveTimeline;

	UPROPERTY(EditAnywhere, DisplayName = "Target Locations", meta = (NoElementDuplicate))
		TArray<FTarget> Locations;
	FVector InitialLocation;
	FTarget* TargetInfo;
	UFUNCTION()
		void NextTarget();
	bool bReverse = false;

	
	
};
