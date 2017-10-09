// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTurret.h"
#include "TankBarrel.h"



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

void UTankTurret::MatchRotation(FVector Direction)
{
	if (!ensure(Barrel)) { return; }
	float DesiredYaw = Direction.Rotation().Yaw;
	float YawDifference = DesiredYaw - Barrel->GetComponentRotation().Yaw;
	UE_LOG(LogTemp, Warning, TEXT("Difference: %f Current: %f"), YawDifference, GetComponentRotation().Yaw);
	if (FMath::Abs(YawDifference) <= MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds)
	{
		AddRelativeRotation(FRotator(0, YawDifference, 0));
		return;
	}

	FRotator DeltaRotation = (FRotator(0, DesiredYaw, 0) - Barrel->GetComponentRotation()).GetNormalized();
	float NewYawDirection = FMath::Sign(DeltaRotation.Yaw) * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
	AddRelativeRotation(FRotator(0, NewYawDirection, 0));

}

void UTankTurret::Initialize(UTankBarrel* BarrelToSet)
{
	Barrel = BarrelToSet;
}
