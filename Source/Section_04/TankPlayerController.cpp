// Copyright 2017 Red Rabbit Games, Inc.

#include "TankPlayerController.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"

// Output parameter
#define OUT


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
	if (GetSightRayHitLocation (OUT HitLocation)) {
		UE_LOG (LogTemp, Warning, TEXT ("Hit location: %s"), *(HitLocation.ToString ()));
		// TODO: Tell controlled tank to aim at this point
	}
}

bool ATankPlayerController::GetSightRayHitLocation (FVector& OutHitLocation) const
{
	FVector LookDirection;
	FVector CameraLocation;
	FVector2D ScreenLocation = GetScreenLocation ();

	// De-project the screen position to a world firection
	if (DeprojectScreenPositionToWorld (
		ScreenLocation.X,
		ScreenLocation.Y,
		OUT CameraLocation,
		OUT LookDirection)) {
		// Line trace along that look direction (up to max range)
		return GetLookVectorHitLocation (CameraLocation, LookDirection, OutHitLocation);
	}

	return false;
}

FVector2D ATankPlayerController::GetScreenLocation () const
{
	// Find the crosshair position in pixel coordinates
	int32 ViewPortSizeX, ViewPortSizeY;

	GetViewportSize (OUT ViewPortSizeX, OUT ViewPortSizeY);

	return FVector2D (
		float (ViewPortSizeX) * CrossHairXLocation,
		float (ViewPortSizeY) * CrossHairYLocation
	);
}

bool ATankPlayerController::GetLookVectorHitLocation (FVector& CameraLocation, FVector& LookDirection, FVector& OutHitLocation) const
{
	/// Setup Query parameters
	//FCollisionQueryParams TraceParameters = FCollisionQueryParams (FName (TEXT ("")), false, GetOwner ());
	FHitResult HitResult;

	auto EndLocation = CameraLocation + LookDirection * LineTraceRange;

	if (GetWorld ()->LineTraceSingleByChannel (OUT HitResult, CameraLocation, EndLocation, ECollisionChannel::ECC_Visibility)) {
		OutHitLocation = HitResult.Location;
		return true;
	}
	/// We didn't get a hit
	OutHitLocation = FVector (0.0f);
	return false;
}
