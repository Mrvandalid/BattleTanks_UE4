// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"



//Fire status enum
UENUM()
enum class EFiringState : uint8
{
	ReadyToFire,
	Aiming,
	Reloading
};


class UTankBarrel;
class UTankTurret;
class AProjectile;

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BATTLETANKS_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UTankAimingComponent();

	UFUNCTION(BlueprintCallable, Category = "Setup")
		void Initialize(UTankBarrel* BarrelToSet, UTankTurret* TurretToSet);

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable, Category = "Gameplay")
		void AimAt(FVector Target);

	UFUNCTION(BlueprintCallable, Category = Gameplay)
		void Fire();

	void AimTowards(FRotator Direction);

	FVector GetBarrelNozzleLocation();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(BlueprintReadOnly, Category = "State")
		EFiringState FiringStatus = EFiringState::Reloading;


private:
	UTankBarrel *Barrel = nullptr;
	UTankTurret *Turret = nullptr;

	void MoveBarrelTowards(FVector Direction);

	UPROPERTY(EditDefaultsOnly, Category = Firing)
		float LaunchSpeed = 100000; // Cm per second = 1000 m/s


	UPROPERTY(EditDefaultsOnly, Category = Setup)
		TSubclassOf<AProjectile> ProjectileBlueprint;

	UPROPERTY(EditDefaultsOnly, Category = Firing)
		float ReloadTime = 3;

	double LastFireTime = 0;

	bool bIsBarrelMoving = true;


};
