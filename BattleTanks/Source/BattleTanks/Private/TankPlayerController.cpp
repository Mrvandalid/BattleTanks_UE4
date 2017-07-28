// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"


void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();
	ControlledTank = GetControlledTank();
	if (ControlledTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("Possessing tank: %s"), *ControlledTank->GetName());
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Not in possession of any tank"));
	}
}

void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AimTowardsCrosshair();
}

ATank* ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

void ATankPlayerController::AimTowardsCrosshair()
{
	if (!ControlledTank) { return; }
	FVector CrosshairHitLocation;
	if (GetSightRayHitLocation(CrosshairHitLocation))
	{
		
	}
}

bool ATankPlayerController::GetSightRayHitLocation(FVector & OutHitLocation)
{
	FVector LookDirection;
	FVector WorldPosition;
	if (GetLookDirection(WorldPosition, LookDirection))
	{
		FVector HitLocation;
		if (GetLineTraceHitLocation(WorldPosition, LookDirection, HitLocation))
		{
			GetControlledTank()->AimAt(HitLocation);
		}
	}
	OutHitLocation = FVector(1, 2, 3);
	//UE_LOG(LogTemp, Warning, TEXT("Camera dir: %s"), *CameraDirection.ToString());
	return true;
}

bool ATankPlayerController::GetLookDirection(FVector& OutCameraPosition, FVector& OutCameraDirection)// Gets the direction the camera is pointing at (as a vector)
{
	int32 ViewportSizeX, ViewportSizeY;
	GetViewportSize(ViewportSizeX, ViewportSizeY);
	FVector2D CrosshairScreenLocation = FVector2D( // Get the crosshair screen position
		ViewportSizeX * CrosshairXPosistion, 
		ViewportSizeY * CrosshairYPosistion
	);

	return DeprojectScreenPositionToWorld(// Deproject the screen position (crosshair position) to world space. Returns true if successful
		CrosshairScreenLocation.X,
		CrosshairScreenLocation.Y,
		OutCameraPosition,
		OutCameraDirection
	);
	
}

//************************************
// Method:    GetCrosshairHitLocation
// FullName:  ATankPlayerController::GetCrosshairHitLocation
// Access:    private 
// Returns:   bool
// Qualifier: Get the vector position from a LineTrace
// Parameter: FVector Start
// Parameter: FVector Direction
// Parameter: FVector & OutHitLocation
//************************************
bool ATankPlayerController::GetLineTraceHitLocation(FVector Start, FVector Direction, FVector & OutHitLocation)
{
	FCollisionQueryParams QueryParams = FCollisionQueryParams(
		FName(), false, GetPawn());

	FHitResult Hit;
	if (GetWorld()->LineTraceSingleByChannel(Hit,
		Start,
		Start + Direction * TraceRange,
		ECollisionChannel::ECC_Visibility,
		QueryParams))
	{
		OutHitLocation = Hit.ImpactPoint;
		return true;
	}
	return false;
}

