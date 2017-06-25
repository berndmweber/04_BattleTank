// Copyright 2017 Red Rabbit Games, Inc.

#include "../Public/TankTrack.h"

// Set throttle between -1 and 1
void UTankTrack::SetThrottle (float Throttle)
{
	// TODO clamp actual throttle value so player can't overdrive
	auto ForceApplied = GetForwardVector () * Throttle * TrackMaxDrivingForce;
	auto ForceLocation = GetComponentLocation ();
	auto TankRoot = Cast<UPrimitiveComponent> (GetOwner ()->GetRootComponent ());
	TankRoot->AddForceAtLocation (ForceApplied, ForceLocation);
}
