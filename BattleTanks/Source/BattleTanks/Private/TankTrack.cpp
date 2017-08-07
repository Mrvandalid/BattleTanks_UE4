// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTrack.h"
#include "GameFramework/Actor.h"


void UTankTrack::SetThrottle(float Throttle)
{
	

	FVector ForceVector = GetForwardVector() * TrackMaxForce * Throttle;
	FVector ForceLocation = GetComponentLocation();

	auto TankRoot = Cast<UStaticMeshComponent>(GetAttachmentRoot());
	//UE_LOG(LogTemp, Warning, TEXT("Attachment root: %s"), *TankRoot->GetName());

	TankRoot->AddForceAtLocation(ForceVector, ForceLocation);
}
