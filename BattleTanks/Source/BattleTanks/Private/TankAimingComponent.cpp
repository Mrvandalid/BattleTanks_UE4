// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"
#include "TankBarrel.h"


// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
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
	DrawDebugPoint(GetWorld(), NozzlePosition, 50, FColor(255, 0, 0));

	//TArray<AActor*> empty;

	FVector ProjectileVelocity;
	bool FoundVelocityVector = UGameplayStatics::SuggestProjectileVelocity(
		GetOwner(),
		ProjectileVelocity,
		NozzlePosition,
		Target,
		LaunchSpeed,
		15,
		ESuggestProjVelocityTraceOption::DoNotTrace
	);

	if (FoundVelocityVector)
	{
		ProjectileVelocity = ProjectileVelocity.GetSafeNormal();

		UE_LOG(LogTemp, Warning, TEXT("Launch speed: %f"), LaunchSpeed);
	}
}

FVector UTankAimingComponent::GetBarrelNozzleLocation()
{
	if (!Barrel) { return FVector(0); }

	return Barrel->GetSocketLocation(FName("Projectile"));
	FRotator BarrelRotation = Barrel->GetComponentRotation();

	FVector BarrelPosition;
	BarrelPosition = Barrel->GetComponentLocation();

	FVector BarrelLength;
	FVector useless;
	Barrel->GetLocalBounds(useless, BarrelLength);
	BarrelLength = FVector(BarrelLength.X, 0, 0);

	BarrelLength = BarrelRotation.RotateVector(BarrelLength);

	FVector BarrelNozzlePosition = BarrelPosition + BarrelLength;

	//DrawDebugSphere(GetWorld(), BarrelNozzlePosition, 50, 10, FColor(255, 0, 0));
	//UE_LOG(LogTemp, Warning, TEXT("Barrel nozzle position: %s"), *BarrelNozzlePosition.ToString());
	return BarrelNozzlePosition;
}

void UTankAimingComponent::MoveBarrelTowards(FVector Direction)
{
	// Calculate the Turret Yaw and barrel Pitch by Direction
	FRotator BarrelRotation = Barrel->GetComponentRotation();
	FRotator DirectionRotator = Direction.Rotation();
	FRotator DeltaRotator = BarrelRotation - DirectionRotator;

	Barrel->ElevateBarrel(5);
}

void UTankAimingComponent::SetBarrel(UTankBarrel* BarrelToSet)
{
	Barrel = BarrelToSet;
}

