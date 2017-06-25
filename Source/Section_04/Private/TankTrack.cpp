// Copyright 2017 Red Rabbit Games, Inc.

#include "../Public/TankTrack.h"

// Set throttle between -1 and 1
void UTankTrack::SetThrottle (float Throttle)
{
	Throttle = FMath::Clamp (Throttle, MinThrottle, MaxThrottle);
	auto ForceApplied = GetForwardVector () * Throttle * TrackMaxDrivingForce;
	auto ForceLocation = GetComponentLocation ();
	auto TankRoot = Cast<UPrimitiveComponent> (GetOwner ()->GetRootComponent ());
	TankRoot->AddForceAtLocation (ForceApplied, ForceLocation);
}
