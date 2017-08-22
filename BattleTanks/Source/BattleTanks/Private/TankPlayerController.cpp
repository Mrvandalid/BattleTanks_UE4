// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"
#include "TankAimingComponent.h"


ATankPlayerController::ATankPlayerController()
{
	
}

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();
	AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
	if (AimingComponent)
	{
		FoundAimingComponent(AimingComponent);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("AimingComponent Not found"));
	}
}

void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AimTowardsCrosshair();
}


void ATankPlayerController::AimTowardsCrosshair()
{
	if (!ensure(AimingComponent)) { return; }
	FVector CrosshairHitLocation;
	FVector CameraLookDirection;
	if (GetSightRayHitLocation(CrosshairHitLocation, CameraLookDirection))
	{
		//UE_LOG(LogTemp, Warning, TEXT("Camera rotation: %s"), *(CameraLookDirection.Rotation() - GetPawn()->GetActorRotation()).ToString());
		if ((CameraLookDirection.Rotation() - GetPawn()->GetActorRotation()).Pitch < -20)
		{
			AimingComponent->AimTowards(CameraLookDirection.Rotation());
			return;
		}
		AimingComponent->AimAt(CrosshairHitLocation);
	}
	else
	{
		AimingComponent->AimTowards(CameraLookDirection.Rotation());
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

