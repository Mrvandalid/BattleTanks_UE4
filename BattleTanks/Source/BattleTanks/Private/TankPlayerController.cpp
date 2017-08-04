// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"
#include "Tank.h"
#include "DrawDebugHelpers.h"


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
	FVector CameraLookDirection;
	if (GetSightRayHitLocation(CrosshairHitLocation, CameraLookDirection))
	{
		//UE_LOG(LogTemp, Warning, TEXT("Camera rotation: %s"), *(CameraLookDirection.Rotation() - GetPawn()->GetActorRotation()).ToString());
		if ((CameraLookDirection.Rotation() - GetPawn()->GetActorRotation()).Pitch < -20)
		{
			GetControlledTank()->AimTowards(CameraLookDirection.Rotation());
			return;
		}
		//UE_LOG(LogTemp, Warning, TEXT("HitLocation: %s"), *CrosshairHitLocation.ToString());
		DrawDebugSphere(GetWorld(), CrosshairHitLocation, 10, 30, FColor(255, 0, 0));
		GetControlledTank()->AimAt(CrosshairHitLocation);
	}
	else
	{
		GetControlledTank()->AimTowards(CameraLookDirection.Rotation());
	}
}

bool ATankPlayerController::GetSightRayHitLocation(FVector & OutHitLocation, FVector& OutLookDirection)
{
	//LookDirection;
	FVector WorldPosition;
	if (GetLookDirection(WorldPosition, OutLookDirection))
	{
		//FVector HitLocation;
		return GetLineTraceHitLocation(WorldPosition, OutLookDirection, OutHitLocation);
	}
	//OutHitLocation = FVector(1, 2, 3);
	//UE_LOG(LogTemp, Warning, TEXT("Camera dir: %s"), *CameraDirection.ToString());
	return false;
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
		FName(), false, GetOwner());
	QueryParams.AddIgnoredActor(GetPawn());

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

