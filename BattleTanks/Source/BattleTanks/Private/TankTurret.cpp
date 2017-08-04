// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTurret.h"




void UTankTurret::RotateTurret(float Yaw)
{
	//UE_LOG(LogTemp, Warning, TEXT("Yaw: %f"), Yaw);
	FRotator CurrentRotation = GetComponentRotation();
	float YawDifference = Yaw - CurrentRotation.Yaw;
	if (FMath::Abs(YawDifference) <= MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds)
	{
		AddRelativeRotation(FRotator(0, YawDifference, 0));
		return;
	}
	FRotator DeltaRotation = (FRotator(0, Yaw, 0) - CurrentRotation).GetNormalized();
	float NewYawDirection = FMath::Sign(DeltaRotation.Yaw);
	AddRelativeRotation(FRotator(0, NewYawDirection * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds, 0));
}
