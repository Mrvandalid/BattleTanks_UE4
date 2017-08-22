// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
//#include "GameFramework/Actor.h"
#include "TankPlayerController.generated.h"

class ATank;
class UTankAimingComponent;
/**
 *
 */
UCLASS()
class BATTLETANKS_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()

public:

	ATankPlayerController();

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category = "Setup")
		ATank* GetControlledTank() const;// The tank instance this controller is possessing

protected:// Variables
	UPROPERTY(EditDefaultsOnly)
		float CrosshairXPosistion = 0.5f;
	UPROPERTY(EditDefaultsOnly)
		float CrosshairYPosistion = 0.33333f;
	UPROPERTY(EditDefaultsOnly)
		float TraceRange = 150000;

	UFUNCTION(BlueprintImplementableEvent, Category = "Setup")
		void FoundAimingComponent(UTankAimingComponent* FoundAimingComponent);


private:// Helper functions

	ATank* ControlledTank = nullptr;

	void AimTowardsCrosshair();

	//True if crosshair trace hits something, and "returns" the location as an out parameter
	bool GetSightRayHitLocation(FVector & OutHitLocation, FVector& OutLookDirection);

	bool GetLookDirection(FVector& OutCameraPosition, FVector& OutCameraDirection);

	bool GetLineTraceHitLocation(FVector Start, FVector Direction, FVector& OutHitLocation);

	UTankAimingComponent* AimingComponent = nullptr;

};
