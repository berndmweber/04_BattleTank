// Copyright 2017 Red Rabbit Games, Inc.

#include "../Public/TankMovementComponent.h"
#include "../Public/TankTrack.h"

void UTankMovementComponent::Initialize (UTankTrack* LeftTrackToSet, UTankTrack* RightTrackToSet)
{
	LeftTrack = LeftTrackToSet;
	RightTrack = RightTrackToSet;
}

void UTankMovementComponent::IntendMoveForward (float Throw)
{
	if (!LeftTrack || !RightTrack) { return; }
	LeftTrack->SetThrottle (Throw);
	RightTrack->SetThrottle (Throw);
	// TODO prevent double speed due to double input
}

void UTankMovementComponent::IntendTurnRight (float Throw)
{
	if (!LeftTrack || !RightTrack) { return; }
	LeftTrack->SetThrottle (-Throw);
	RightTrack->SetThrottle (Throw);
	// TODO prevent double speed due to double input
}
