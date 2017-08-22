// Fill out your copyright notice in the Description page of Project Settings.

#include "TankMovementComponent.h"
#include  "TankTrack.h"

void UTankMovementComponent::Initialize(UTankTrack* LeftTrackToSet, UTankTrack* RightTrackToSet)
{
	LeftTrack = LeftTrackToSet;
	RightTrack = RightTrackToSet;
}

void UTankMovementComponent::IntendMoveForward(float Throw)
{
	if (!ensure(LeftTrack && RightTrack)) { return; }
	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(Throw);
}

void UTankMovementComponent::IntendTurnRight(float Throw)
{
	if (!ensure(LeftTrack && RightTrack)) { return; }
	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(-Throw);
}

void UTankMovementComponent::RequestDirectMove(const FVector& Direction, bool ForceMaxSpeed)
{
	//UE_LOG(LogTemp, Warning, TEXT("%s moving to %s"), *GetOwner()->GetName(), *Direction.ToString());
	FVector DesiredDirection = Direction.GetSafeNormal();
	FVector CurrentDirection = GetOwner()->GetActorForwardVector().GetSafeNormal();
	FVector CurrentRightDirection = GetOwner()->GetActorRightVector().GetSafeNormal();

	float ForwardThrow = FVector::DotProduct(CurrentDirection, DesiredDirection);
	float TurnRightThrow = FMath::Sign(FVector::DotProduct(CurrentRightDirection, DesiredDirection));

	IntendMoveForward(ForwardThrow);
	IntendTurnRight(TurnRightThrow);

}
