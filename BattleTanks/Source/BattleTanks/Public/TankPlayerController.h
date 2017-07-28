// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Tank.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
//#include "GameFramework/Actor.h"
#include "TankPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class BATTLETANKS_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	ATank* GetControlledTank() const;// The tank instance this controller is possessing

private:// Variables
	UPROPERTY(EditAnywhere)
		float CrosshairXPosistion = 0.5f;
	UPROPERTY(EditAnywhere)
		float CrosshairYPosistion = 0.33333f;
	UPROPERTY(EditAnywhere)
		float TraceRange = 150000;

private:// Helper functions
	ATank* ControlledTank = nullptr;

	void AimTowardsCrosshair();

	//True if crosshair trace hits something, and "returns" the location as an out parameter
	bool GetSightRayHitLocation(FVector & OutHitLocation);

	bool GetLookDirection(FVector& OutCameraPosition, FVector& OutCameraDirection);

	bool GetLineTraceHitLocation(FVector Start, FVector Direction, FVector& OutHitLocation);
	
};
