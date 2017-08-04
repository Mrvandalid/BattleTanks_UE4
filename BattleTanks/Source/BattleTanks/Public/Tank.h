// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

class UTankBarrel;
class UTankAimingComponent;

UCLASS()
class BATTLETANKS_API ATank : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ATank();

	void AimAt(FVector Target);

	void AimTowards(FRotator Direction);

	UFUNCTION(BlueprintCallable, Category = Setup)
		void SetBarrel(UTankBarrel *BarrelToSet);

	UFUNCTION(BlueprintCallable, Category = Setup)
		void SetTurret(UTankTurret* TurretToSet);

	UFUNCTION(BlueprintCallable, Category = Gameplay)
		void Fire();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UTankAimingComponent *AimingComponent = nullptr;

//public:	
//	// Called every frame
//	virtual void Tick(float DeltaTime) override;

private:
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditAnywhere)
		bool SetActive = true;

	UPROPERTY(EditAnywhere, Category = Firing)
		float LaunchSpeed = 100000; // Cm per second = 1000 m/s
	
};
