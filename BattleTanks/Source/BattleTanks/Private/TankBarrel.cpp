// Fill out your copyright notice in the Description page of Project Settings.

#include "TankBarrel.h"
//#include "UnrealMath.h"



void UTankBarrel::ElevateBarrel(float Pitch)
{
	Pitch = FMath::Clamp(Pitch, MinDegrees, MaxDegrees);
	float CurrentPitch = GetComponentRotation().Pitch;
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
