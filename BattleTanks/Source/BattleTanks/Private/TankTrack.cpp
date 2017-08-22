// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTrack.h"
#include "GameFramework/Actor.h"


void UTankTrack::SetThrottle(float Throttle)
{
	

	FVector ForceVector = GetForwardVector() * TrackMaxForce * Throttle;
	FVector ForceLocation = GetComponentLocation();

	auto TankRoot = Cast<UPrimitiveComponent>(GetAttachmentRoot());
	//UE_LOG(LogTemp, Warning, TEXT("Throttle: %f"), Throttle);

	TankRoot->AddForceAtLocation(ForceVector, ForceLocation);
}
