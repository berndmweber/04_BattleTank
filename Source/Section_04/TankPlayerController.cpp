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
	FVector WorldDirection;

	// De-project the screen position to a world firection
	if (!GetLookDirection (GetScreenLocation (), WorldDirection)) {
		UE_LOG (LogTemp, Error, TEXT ("Unable to determine World location based on screen"));
	}
	// Line trace along that look direction (up to max range)

	// Compute ray staight out at crosshair location
	// Check if it intersects anything
		// if yes assign hitlocation and return true
		// else return false
	return true;
}

FVector2D ATankPlayerController::GetScreenLocation () const
{
	// Find the crosshair position in pixel coordinates
	int32 ViewPortSizeX, ViewPortSizeY;

	GetViewportSize (ViewPortSizeX, ViewPortSizeY);

	return FVector2D (
		float (ViewPortSizeX) * CrossHairXLocation,
		float (ViewPortSizeY) * CrossHairYLocation
	);
}

bool ATankPlayerController::GetLookDirection (FVector2D ScreenLocation, FVector &OutLookDirection) const
{
	FVector CameraWorldLocation;

	// De-project the screen position to a world firection
	return DeprojectScreenPositionToWorld (ScreenLocation.X, ScreenLocation.Y, CameraWorldLocation, OutLookDirection);
}
