// Fill out your copyright notice in the Description page of Project Settings.

#include "PuzzlePlatformsGameInstance.h"
#include "Engine/Engine.h"


UPuzzlePlatformsGameInstance::UPuzzlePlatformsGameInstance(const FObjectInitializer & ObjectIntializer)
{
	UE_LOG(LogTemp, Warning, TEXT("PuzzlePlatformsGameInstance_Constructor"));
}

void UPuzzlePlatformsGameInstance::Init()
{
	Super::Init();

	UE_LOG(LogTemp, Warning, TEXT("PuzzlePlatformsGameInstance_Init"));


}

void UPuzzlePlatformsGameInstance::Host()
{
	//UE_LOG(LogTemp, Warning, TEXT("Host GameInstans"));
	UEngine* engine = GetEngine();
	engine->AddOnScreenDebugMessage(-1, 2, FColor::Green, TEXT("This is Host GameInstacne"));
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Purple, TEXT("This is Host GameInstance"));
}

void UPuzzlePlatformsGameInstance::Join(const FString& Adress)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Purple, FString::Printf(TEXT("Adress = %s"), *Adress));
}
