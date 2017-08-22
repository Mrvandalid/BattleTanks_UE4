// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/NavMovementComponent.h"
#include "TankMovementComponent.generated.h"

class UTankTrack;

/**
 * 
 */
UCLASS(meta = (BlueprintSpawnableComponent))
class BATTLETANKS_API UTankMovementComponent : public UNavMovementComponent
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, Category = Setup)
		void Initialize(UTankTrack* LeftTrackToSet, UTankTrack* RightTrackToSet);

	UFUNCTION(BlueprintCallable, Category = Gameplay)
		void IntendMoveForward(float Throw);

	UFUNCTION(BlueprintCallable, Category = Gameplay)
		void IntendTurnRight(float Throw);

	
		
private:
	// Override the superclass definition
	virtual void RequestDirectMove(const FVector& Direction, bool ForceMaxSpeed) override;

	UTankTrack* LeftTrack;
	UTankTrack* RightTrack;
};
