// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankBarrel.generated.h"

/**
 *
 */
UCLASS(meta = (BlueprintSpawnableComponent), HideCategories = ("Collision", "Physics"))
class BATTLETANKS_API UTankBarrel : public UStaticMeshComponent
{
	GENERATED_BODY()

public:
	void ElevateBarrel(float Pitch);


private:
	UPROPERTY(EditAnywhere, Category = Setup)
		float MaxDegreesPerSecond = 15;

	UPROPERTY(EditAnywhere, Category = Setup)
		float MaxDegrees = 30;

	UPROPERTY(EditAnywhere, Category = Setup)
		float MinDegrees = -2;
};
