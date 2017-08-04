// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"
#include "TankAimingComponent.h"

// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	AimingComponent = CreateDefaultSubobject<UTankAimingComponent>(FName("Aiming Component"));
}

void ATank::AimAt(FVector Target)
{
	if (!SetActive) { return; }
	AimingComponent->AimAt(Target, LaunchSpeed);
}

void ATank::AimTowards(FRotator Direction)
{
	AimingComponent->AimTowards(Direction, LaunchSpeed);
}

void ATank::SetBarrel(UTankBarrel* BarrelToSet)
{
	AimingComponent->SetBarrel(BarrelToSet);
}

void ATank::SetTurret(UTankTurret* TurretToSet)
{
	AimingComponent->SetTurret(TurretToSet);
}

void ATank::Fire()
{
	UE_LOG(LogTemp, Warning, TEXT("Fire was called"));
}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
//void ATank::Tick(float DeltaTime)
//{
//	Super::Tick(DeltaTime);
//}

// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

