// Copyright 2017 Red Rabbit Games, Inc.

#include "TankPlayerController.h"
#include "Public/TankAimingComponent.h"
#include "Public/Tank.h"
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

	auto Tank = GetPawn ();
	if (ensure (Tank)) {
		AimingComponent = Tank->FindComponentByClass<UTankAimingComponent> ();
		if (ensure (AimingComponent)) {
			FoundAimingComponent (AimingComponent);
		}
		else {
			UE_LOG (LogTemp, Error, TEXT ("Player Controller can't find aiming component at BeginPlay"));
		}
	}
}

void ATankPlayerController::AimTowardsCrosshair ()
{
	if (!ensure (AimingComponent)) { return; }

	FVector HitLocation; // Out parameter

	// Get world location if linetrace through crosshair
	// If it hits the landscape
	bool bGotHitLocation = GetSightRayHitLocation (OUT HitLocation);
	if (bGotHitLocation) {
		AimingComponent->AimAt (HitLocation);
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

void ATankPlayerController::SetPawn (APawn * InPawn)
{
	Super::SetPawn (InPawn);

	if (ensure (InPawn)) {
		auto PossessedTank = Cast<ATank> (InPawn);

		// Subscribe our local method to the tank's death event
		PossessedTank->OnDeath.AddUniqueDynamic (this, &ATankPlayerController::OnTankDeath);
	}
}

void ATankPlayerController::OnTankDeath ()
{
	StartSpectatingOnly ();
}
