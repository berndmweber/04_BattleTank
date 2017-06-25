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
}

void UTankMovementComponent::IntendTurnRight (float Throw)
{
	if (!LeftTrack || !RightTrack) { return; }
	LeftTrack->SetThrottle (-Throw);
	RightTrack->SetThrottle (Throw);
}

void UTankMovementComponent::RequestDirectMove (const FVector& MoveVelocity, bool bForceMaxSpeed)
{
	// No need to call super since we're replacing the logic
	auto TankForward = GetOwner ()->GetActorForwardVector ().GetSafeNormal ();
	auto AIForwadIntention = MoveVelocity.GetSafeNormal ();

	float ForwardThrow = FVector::DotProduct (TankForward, AIForwadIntention);
	IntendMoveForward (ForwardThrow);

	auto RightThrow = FVector::CrossProduct (TankForward, AIForwadIntention);
	IntendTurnRight (RightThrow.Z);
}
