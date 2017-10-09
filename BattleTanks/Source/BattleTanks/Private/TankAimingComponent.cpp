// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"
#include "Projectile.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "DrawDebugHelpers.h"


// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UTankAimingComponent::Initialize(UTankBarrel* BarrelToSet, UTankTurret* TurretToSet)
{
	Barrel = BarrelToSet;
	Turret = TurretToSet;

	Turret->Initialize(Barrel);
}


// Called when the game starts
void UTankAimingComponent::BeginPlay()
{
	Super::BeginPlay();

	LastFireTime = FPlatformTime::Seconds();

	UE_LOG(LogTemp, Warning, TEXT("Aimingcomponent begin play"));

}


// Called every frame
void UTankAimingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if(FPlatformTime::Seconds() - LastFireTime < ReloadTime)
	{
		FiringStatus = EFiringState::Reloading;
	}
	else if(bIsBarrelMoving)
	{
		FiringStatus = EFiringState::Aiming;
	}
	else
	{
		FiringStatus = EFiringState::ReadyToFire;
	}
}

void UTankAimingComponent::AimAt(FVector Target)
{
	if (!ensure(Barrel)) { return; }

	FVector NozzlePosition = GetBarrelNozzleLocation();

	//TArray<AActor*> empty;

	FVector ProjectilDirection;
	bool FoundVelocityVector = UGameplayStatics::SuggestProjectileVelocity(
		GetOwner(),
		ProjectilDirection,
		NozzlePosition,
		Target,
		LaunchSpeed,
		false,
		15,
		false,
		ESuggestProjVelocityTraceOption::DoNotTrace
	);
	float TimeDelta = GetWorld()->GetTimeSeconds();
	if (FoundVelocityVector)
	{
		ProjectilDirection = ProjectilDirection.GetSafeNormal();
		MoveBarrelTowards(ProjectilDirection);
	}
	else
	{
		bIsBarrelMoving = true;
	}
	
}

void UTankAimingComponent::Fire()
{
	if (!ensure(Barrel && ProjectileBlueprint)) { return; }

	

	if (FiringStatus != EFiringState::Reloading)
	{
		//UE_LOG(LogTemp, Warning, TEXT("Found socket: %s"), *Barrel->GetSocketByName(FName("Projectile"))->SocketName.ToString());
		FVector Location = Barrel->GetSocketLocation(FName("Projectile"));
		FRotator Rotation = Barrel->GetSocketRotation(FName("Projectile"));
		AProjectile* Projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileBlueprint, Location, Rotation);

		Projectile->LaunchProjectile(LaunchSpeed);

		LastFireTime = FPlatformTime::Seconds();
	}
}

void UTankAimingComponent::AimTowards(FRotator Direction)
{
	if (!ensure(Barrel) || !ensure(Turret)) { return; }
	Barrel->ElevateBarrel(Direction.Pitch);
	Turret->RotateTurret(Direction.Yaw);
}

FVector UTankAimingComponent::GetBarrelNozzleLocation()
{
	if (!ensure(Barrel)) { return FVector(0); }

	return Barrel->GetSocketLocation(FName("Projectile"));
}

void UTankAimingComponent::MoveBarrelTowards(FVector Direction)
{
	FRotator DirectionRotator = Direction.Rotation();

	DrawDebugLine(GetWorld(), GetOwner()->GetActorLocation() + FVector::UpVector * 500, GetOwner()->GetActorLocation() + FVector::UpVector * 500 + Direction * 1000, FColor::Green, false, -1, 0, 5);
	DrawDebugLine(GetWorld(), GetOwner()->GetActorLocation() + FVector::UpVector * 500, GetOwner()->GetActorLocation() + FVector::UpVector * 500 + Barrel->GetComponentRotation().Vector() * 1000, FColor::Red, false, -1, 0, 5);

	if(Barrel->GetComponentRotation().Vector().Equals(Direction, 0.0005f))
	{
		bIsBarrelMoving = false;
		return;
	}
	bIsBarrelMoving = true;

	Barrel->MatchDirection(Direction);
	Turret->MatchRotation(Direction);
	//Barrel->ElevateBarrel(DirectionRotator.Pitch);
	//Turret->RotateTurret(DirectionRotator.Yaw);
}

