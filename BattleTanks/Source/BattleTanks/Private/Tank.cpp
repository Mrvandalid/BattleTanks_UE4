// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"
#include "GenericApplication.h"

// Sets default values
ATank::ATank()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}



bool ATank::GetIsActive() const
{
	return IsActive;
}




// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();
	//UE_LOG(LogTemp, Warning, TEXT("Is gamepad connected: %d"), GenericApplication::IsGamepadAttached())
	
}



