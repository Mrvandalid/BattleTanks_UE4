// Fill out your copyright notice in the Description page of Project Settings.

#include "Projectile.h"


// Sets default values
AProjectile::AProjectile()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(FName("Projectile Movement"));
	MovementComponent->bAutoActivate = false;

}

void AProjectile::LaunchProjectile(float LaunchSpeed)
{
	if (!ensure(MovementComponent)) { return; }
	MovementComponent->Activate();
	MovementComponent->SetVelocityInLocalSpace(FVector::ForwardVector * LaunchSpeed);
}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

