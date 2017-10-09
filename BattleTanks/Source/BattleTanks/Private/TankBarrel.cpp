// Fill out your copyright notice in the Description page of Project Settings.

#include "TankBarrel.h"
//#include "UnrealMath.h"



void UTankBarrel::ElevateBarrel(float Pitch)
{
	float RelativePitch = GetOwner()->GetActorRotation().Pitch;
	Pitch = FMath::Clamp(Pitch, MinDegrees /*+ RelativePitch*/, MaxDegrees /*+ RelativePitch*/);
	float CurrentPitch = GetRelativeTransform().GetRotation().Rotator().Pitch;
	float PitchDifference = Pitch - CurrentPitch;

	//UE_LOG(LogTemp, Warning, TEXT("Desired: %f Current: %f Difference: %f"), Pitch, CurrentPitch, PitchDifference);

	if (FMath::Abs(PitchDifference) <= MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds)// If the remaining distance can be cleared on the next frame, add remaining distance.
	{
		AddRelativeRotation(FRotator(PitchDifference, 0, 0));
		return;
	}

	float NewPitch = FMath::Sign(PitchDifference) * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;// If not, add the maximum amount of distance, determined by MaxDegreesPerSecond
	AddRelativeRotation(FRotator(NewPitch, 0, 0));
	// Rotate the barrel to rotation at desired speed
	//UE_LOG(LogTemp, Warning, TEXT("ElevateBarrel called"));
}

void UTankBarrel::MatchDirection(FVector Direction)
{
	float DesiredPitch = Direction.Rotation().Pitch;
	float CurrentPitch = GetComponentRotation().Pitch;
	float PitchDifference = DesiredPitch - CurrentPitch;

	float NewPitch = FMath::Clamp(PitchDifference + RelativeRotation.Pitch, MinDegrees, MaxDegrees);



	if (FMath::Abs(PitchDifference) <= MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds)// If the remaining distance can be cleared on the next frame, add remaining distance.
	{
		AddRelativeRotation(FRotator(PitchDifference, 0, 0));
		return;
	}
	NewPitch = FMath::Sign(PitchDifference) * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
	NewPitch = FMath::Clamp(NewPitch + RelativeRotation.Pitch, MinDegrees, MaxDegrees);
	
	SetRelativeRotation(FRotator(NewPitch, 0, 0));

	//UE_LOG(LogTemp, Warning, TEXT("Difference: %f NewPitch: %f"), PitchDifference, NewPitch);
}

void UTankBarrel::SetNewPitch(float PitchDifference)
{
	float NewPitch = FMath::Clamp(PitchDifference + RelativeRotation.Pitch, MinDegrees, MaxDegrees);

	if(FMath::Abs(NewPitch) <= MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds)
	{
		SetRelativeRotation(FRotator(NewPitch, 0, 0));
		return;
	}

}
