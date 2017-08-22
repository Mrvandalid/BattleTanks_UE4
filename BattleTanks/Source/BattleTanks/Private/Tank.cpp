// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"
#include "TankAimingComponent.h"
#include "Engine/World.h"
#include "Projectile.h"
#include "TankBarrel.h"
#include "GameFramework/PlayerController.h"
#include "GenericApplication.h"

// Sets default values
ATank::ATank()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

void ATank::AimAt(FVector Target) const
{
}

void ATank::AimTowards(FRotator Direction) const
{
}

//UTankAimingComponent* ATank::GetAimingComponent() const
//{
//	/*UTankAimingComponent* AimingComponent = Cast<UTankAimingComponent>(GetComponentByClass(TSubclassOf<UTankAimingComponent>()));
//	if(!AimingComponent)
//	{
//		UE_LOG(LogTemp, Warning, TEXT("AimingComponent not found"));
//		GetWorld()->GetFirstPlayerController()->ConsoleCommand("quit");
//	}*/
//	return nullptr; // AimingComponent;
//}

//void ATank::AimAt(FVector Target) const
//{
//	if (!IsActive) { return; }
//	AimingComponent->AimAt(Target, LaunchSpeed);
//}
//
//void ATank::AimTowards(FRotator Direction) const
//{
//	AimingComponent->AimTowards(Direction, LaunchSpeed);
//}

bool ATank::GetIsActive() const
{
	return IsActive;
}

//void ATank::SetBarrel(UTankBarrel* BarrelToSet)
//{
//	Barrel = BarrelToSet;
//	AimingComponent->SetBarrel(BarrelToSet);
//}
//
//void ATank::SetTurret(UTankTurret* TurretToSet)
//{
//	AimingComponent->SetTurret(TurretToSet);
//}

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

float ATank::GetLaunchSpeed() const
{
	return LaunchSpeed;
}


