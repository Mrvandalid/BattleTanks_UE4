// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankBarrel.generated.h"

/**
 *
 */
UCLASS(meta = (BlueprintSpawnableComponent)/*, HideCategories = ("Collision", "Physics")*/)
class BATTLETANKS_API UTankBarrel : public UStaticMeshComponent
{
	GENERATED_BODY()

public:
	void ElevateBarrel(float Pitch);

	void MatchDirection(FVector Direction);

	void SetNewPitch(float PitchDifference);


private:
	UPROPERTY(EditDefaultsOnly, Category = Setup)
		float MaxDegreesPerSecond = 15;

	UPROPERTY(EditDefaultsOnly, Category = Setup)
		float MaxDegrees = 30;

	UPROPERTY(EditDefaultsOnly, Category = Setup)
		float MinDegrees = -2;
};
