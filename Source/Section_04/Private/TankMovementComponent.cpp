// Copyright 2017 Red Rabbit Games, Inc.

#include "../Public/TankMovementComponent.h"
#include "../Public/TankTrack.h"

void UTankMovementComponent::Initialize (UTankTrack* LeftTrackToSet, UTankTrack* RightTrackToSet)
{
	if (!LeftTrackToSet || !RightTrackToSet) { return; }
	LeftTrack = LeftTrackToSet;
	RightTrack = RightTrackToSet;
}

void UTankMovementComponent::IntendMoveForward (float Throw)
{
	if (!LeftTrack || !RightTrack) { return; }
	UE_LOG (LogTemp, Warning, TEXT ("Intend move forward throw: %f"), Throw);
	LeftTrack->SetThrottle (Throw);
	RightTrack->SetThrottle (Throw);
	// TODO prevent double speed due to double input
}
