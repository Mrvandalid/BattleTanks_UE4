// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankTurret.generated.h"

/**
 *
 */

class UTankBarrel;

UCLASS(meta = (BlueprintSpawnableComponent))
class BATTLETANKS_API UTankTurret : public UStaticMeshComponent
{
	GENERATED_BODY()

public:
	void RotateTurret(float Yaw);

	void MatchRotation(FVector Direction);

	UFUNCTION(BlueprintCallable)
		void Initialize(UTankBarrel* BarrelToSet);

private:
	UPROPERTY(EditDefaultsOnly)
		float MaxDegreesPerSecond = 20;

	UTankBarrel* Barrel = nullptr;

	
};
