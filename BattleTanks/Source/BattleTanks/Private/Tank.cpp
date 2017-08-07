// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"
#include "TankAimingComponent.h"
#include "Engine/World.h"
#include "TankBarrel.h"
#include "Projectile.h"
#include "TankMovementComponent.h"
#include "GenericApplication.h"

// Sets default values
ATank::ATank()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	AimingComponent = CreateDefaultSubobject<UTankAimingComponent>(FName("Aiming Component"));
	//MovementComponent = CreateDefaultSubobject<UTankMovementComponent>(FName("Movement Component"));
}

void ATank::AimAt(FVector Target) const
{
	if (!SetActive) { return; }
	AimingComponent->AimAt(Target, LaunchSpeed);
}

void ATank::AimTowards(FRotator Direction) const
{
	AimingComponent->AimTowards(Direction, LaunchSpeed);
}

void ATank::SetBarrel(UTankBarrel* BarrelToSet) 
{
	Barrel = BarrelToSet;
	AimingComponent->SetBarrel(BarrelToSet);
}

void ATank::SetTurret(UTankTurret* TurretToSet) 
{
	AimingComponent->SetTurret(TurretToSet);
}

void ATank::Fire()
{
	bool isReloaded = (FPlatformTime::Seconds() - LastFireTime) > ReloatTime;

	if (Barrel && isReloaded)
	{
		//UE_LOG(LogTemp, Warning, TEXT("Found socket: %s"), *Barrel->GetSocketByName(FName("Projectile"))->SocketName.ToString());
		FVector Location = Barrel->GetSocketLocation(FName("Projectile"));
		FRotator Rotation = Barrel->GetSocketRotation(FName("Projectile"));
		AProjectile* Projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileBlueprint, Location, Rotation);

		Projectile->LaunchProjectile(LaunchSpeed);

		LastFireTime = FPlatformTime::Seconds();
	}
}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();
	//UE_LOG(LogTemp, Warning, TEXT("Is gamepad connected: %d"), GenericApplication::IsGamepadAttached())
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

