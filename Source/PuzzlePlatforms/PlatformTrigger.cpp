// Fill out your copyright notice in the Description page of Project Settings.

#include "PlatformTrigger.h"

#include "Components/BoxComponent.h"

#include "MovingPlatform.h"
#include "Containers/Array.h"


// Sets default values
APlatformTrigger::APlatformTrigger()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	TriggerVolume = CreateDefaultSubobject<UBoxComponent>(FName("Trigger Volume"));
	
	if (!ensure(TriggerVolume != nullptr)) return;
	
	RootComponent = TriggerVolume;

	TriggerVolume->OnComponentBeginOverlap.AddDynamic(this, &APlatformTrigger::OnOverlapBegin); // Register OnOverlapBegin() function
	TriggerVolume->OnComponentEndOverlap.AddDynamic(this, &APlatformTrigger::OnOverlapEnd);     // Register OnOverlapEnd() function

}

// Called when the game starts or when spawned
void APlatformTrigger::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APlatformTrigger::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APlatformTrigger::OnOverlapBegin(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	UE_LOG(LogTemp, Warning, TEXT("Overlap Activated"));
	//if (!ensure(PlatformsToTrigger)) return;
	for (auto Platform : PlatformsToTrigger)
	{
		if (!ensure(Platform)) return;  // without UnrealEditor is crashed when we open BP_PlatformTrigger
		Platform->AddActiveTrigger();   // Because virtual function OnOverlapBegin() is called every time when we open BP_PlatformTrigger despite we start or not game
	}
}

void APlatformTrigger::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	UE_LOG(LogTemp, Warning, TEXT("Overlap Deactivated"));
	for (auto Platform : PlatformsToTrigger)
	{
		if (!ensure(Platform)) return;    // without UnrealEditor is crashed when we open BP_PlatformTrigger
		Platform->RemoveActiveTrigger();  // Because virtual function OnOverlapEnd() is called every time when we open BP_PlatformTrigger despite we start or not game
	}
}

