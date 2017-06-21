// Copyright 2017 Red Rabbit Games, Inc.

#include "TankPlayerController.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"


void ATankPlayerController::Tick (float DeltaTime)
{
	Super::Tick (DeltaTime);

	AimTowardsCrosshair ();
}

void ATankPlayerController::BeginPlay ()
{
	Super::BeginPlay ();

	auto Tank = GetControlledTank ();
	if (Tank) {
		UE_LOG (LogTemp, Warning, TEXT ("PlayerControlled Tank: %s"), *(Tank->GetName ()));
	}
	else {
		UE_LOG (LogTemp, Warning, TEXT ("PlayerController not possesing a tank"));
	}
}

ATank* ATankPlayerController::GetControlledTank () const
{
	return Cast<ATank> (GetPawn ());
}

void ATankPlayerController::AimTowardsCrosshair ()
{
	ATank* ControlledTank = GetControlledTank ();
	if (!ControlledTank) { return; }

	FVector HitLocation; // Out parameter

	// Get world location if linetrace through crosshair
	// If it hits the landscape
	if (GetSightRayHitLocation (HitLocation)) {
		UE_LOG (LogTemp, Warning, TEXT ("Hit location: %s"), *(HitLocation.ToString ()));
		// TODO: Tell controlled tank to aim at this point
	}
}

bool ATankPlayerController::GetSightRayHitLocation (FVector& OutHitLocation) const
{
	OutHitLocation = FVector (1.0f);
	//FRotator PlayerViewPointRotation;
	//FVector LineTraceStart;

	//// Need this to determine the line trace vector
	//GetWorld ()->GetFirstPlayerController ()->GetPlayerViewPoint (
	//	LineTraceStart,
	//	PlayerViewPointRotation
	//);
	
	// Compute ray staight out at crosshair location
	// Check if it intersects anything
		// if yes assign hitlocation and return true
		// else return false
	return false;
}
