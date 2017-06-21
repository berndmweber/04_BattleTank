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
	// Find the crosshair position in pixel coordinates
	int32 ViewPortSizeX, ViewPortSizeY;

	GetViewportSize (ViewPortSizeX, ViewPortSizeY);

	FVector2D ScreenLocation = FVector2D(
		float (ViewPortSizeX) * CrossHairXLocation,
		float (ViewPortSizeY) * CrossHairYLocation
	);

	// De-project the screen position to a world firection
	// Line trace along that look direction (up to max range)

	OutHitLocation = FVector (ScreenLocation, 0.0f);
	
	// Compute ray staight out at crosshair location
	// Check if it intersects anything
		// if yes assign hitlocation and return true
		// else return false
	return true;
}
