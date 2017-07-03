// Copyright 2017 Red Rabbit Games, Inc.

#include "../Public/TankTrack.h"
#include "Engine/World.h"

UTankTrack::UTankTrack () {
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
}

// Called when the game starts or when spawned
void UTankTrack::BeginPlay ()
{
	Super::BeginPlay ();

	OnComponentHit.AddDynamic (this, &UTankTrack::OnHit);
}

void UTankTrack::OnHit (UPrimitiveComponent * HitComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, FVector NormalImpulse, const FHitResult & Hit)
{
	DriveTrack ();
	ApplySidewaysForce ();
	CurrentThrottle = 0;
}

void UTankTrack::ApplySidewaysForce ()
{
	// Calculate the slippage speed
	auto SlippageSpeed = FVector::DotProduct (GetRightVector (), GetComponentVelocity ());
	// Work out the required acceleration  this frame to correct
	auto DeltaTime = GetWorld ()->GetDeltaSeconds ();
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
	CurrentThrottle = FMath::Clamp<float> (CurrentThrottle + Throttle, MinThrottle, MaxThrottle);
}

void UTankTrack::DriveTrack ()
{
	auto ForceApplied = GetForwardVector () * CurrentThrottle * TrackMaxDrivingForce;
	auto ForceLocation = GetComponentLocation ();
	auto TankRoot = Cast<UPrimitiveComponent> (GetOwner ()->GetRootComponent ());
	TankRoot->AddForceAtLocation (ForceApplied, ForceLocation);
}
