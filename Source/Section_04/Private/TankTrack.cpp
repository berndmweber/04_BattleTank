// Copyright 2017 Red Rabbit Games, Inc.

#include "../Public/TankTrack.h"

UTankTrack::UTankTrack () {
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}

void UTankTrack::TickComponent (float DeltaTime, ELevelTick TickType, FActorComponentTickFunction * ThisTickFunction)
{
	Super::TickComponent (DeltaTime, TickType, ThisTickFunction);

	// Calculate the slippage speed
	auto SlippageSpeed = FVector::DotProduct (GetRightVector (), GetComponentVelocity ());
	// Work out the required acceleration  this frame to correct
	auto CorrectionAcceleration = -SlippageSpeed / DeltaTime * GetRightVector ();
	// Calculate and apply side-ways force (F = m * a)
	auto TankRoot = Cast<UStaticMeshComponent> (GetOwner ()->GetRootComponent ());
	if (ensure (TankRoot)) {
		auto CorrectionForce = (TankRoot->GetMass () * CorrectionAcceleration) / 2; // Two Tracks
		TankRoot->AddForce (CorrectionForce);
	}
}

// Set throttle between -1 and 1
void UTankTrack::SetThrottle (float Throttle)
{
	Throttle = FMath::Clamp (Throttle, MinThrottle, MaxThrottle);
	auto ForceApplied = GetForwardVector () * Throttle * TrackMaxDrivingForce;
	auto ForceLocation = GetComponentLocation ();
	auto TankRoot = Cast<UPrimitiveComponent> (GetOwner ()->GetRootComponent ());
	TankRoot->AddForceAtLocation (ForceApplied, ForceLocation);
}
