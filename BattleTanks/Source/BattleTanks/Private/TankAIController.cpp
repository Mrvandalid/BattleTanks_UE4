// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
#include "TankAimingComponent.h"
#include "../Public/TankAIController.h"


ATankAIController::ATankAIController()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
}



void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!Cast<ATank>(GetPawn())->GetIsActive()) { return; }
	//UE_LOG(LogTemp, Warning, TEXT("AI Tick"));
	UTankAimingComponent* ThisTankAimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
	ATank* PlayerTank = Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());

	if (!ensure(ThisTankAimingComponent && PlayerTank)) { return; }

	//if (!ThisTank->GetIsActive()) { return; } //TODO fix IsActive functionality

	MoveToActor(PlayerTank, AcceptanceRadius);

	ThisTankAimingComponent->AimAt(PlayerTank->GetActorLocation());

	//ThisTankAimingComponent->Fire(); //TODO refactor Fire() from tank to aimingcomponent
}


