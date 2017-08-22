// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"
//#include "DrawDebugHelpers.h"
#include "TankBarrel.h"
#include "TankTurret.h"


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
}


// Called when the game starts
void UTankAimingComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...

}


// Called every frame
void UTankAimingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UTankAimingComponent::AimAt(FVector Target, float LaunchSpeed)
{
	if (!Barrel) { return; }

	FVector NozzlePosition = GetBarrelNozzleLocation();

	//TArray<AActor*> empty;

	FVector ProjectileVelocity;
	bool FoundVelocityVector = UGameplayStatics::SuggestProjectileVelocity(
		GetOwner(),
		ProjectileVelocity,
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
		ProjectileVelocity = ProjectileVelocity.GetSafeNormal();
		MoveBarrelTowards(ProjectileVelocity);
		//UE_LOG(LogTemp, Warning, TEXT("%f found aim direction: %s"), TimeDelta, *ProjectileVelocity.ToString());
	}
	/*else
	{
		UE_LOG(LogTemp, Warning, TEXT("%f did not find aim direction: %s"), TimeDelta, *ProjectileVelocity.ToString());
	}*/
}

void UTankAimingComponent::AimTowards(FRotator Direction, float LaunchSpeed)
{
	if (!Barrel) { return; }
	Barrel->ElevateBarrel(Direction.Pitch);
	Turret->RotateTurret(Direction.Yaw);
}

FVector UTankAimingComponent::GetBarrelNozzleLocation()
{
	if (!Barrel) { return FVector(0); }

	return Barrel->GetSocketLocation(FName("Projectile"));
}

void UTankAimingComponent::MoveBarrelTowards(FVector Direction)
{
	FRotator DirectionRotator = Direction.Rotation();

	Barrel->ElevateBarrel(DirectionRotator.Pitch);
	Turret->RotateTurret(DirectionRotator.Yaw);
}

