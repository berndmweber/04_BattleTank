// Copyright 2017 Red Rabbit Games, Inc.

#include "TankPlayerController.h"


void ATankPlayerController::BeginPlay ()
{
	Super::BeginPlay ();

	auto Tank = GetControlledTank ();
	if (Tank) {
		UE_LOG (LogTemp, Warning, TEXT ("Controlled Tank: %s"), *(Tank->GetName ()));
	}
	else {
		UE_LOG (LogTemp, Warning, TEXT ("PlaerController not possesing a tank"));
	}
}

ATank* ATankPlayerController::GetControlledTank () const
{
	return Cast<ATank> (GetPawn ());
}
