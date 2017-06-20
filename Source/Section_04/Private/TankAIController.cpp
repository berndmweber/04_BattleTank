// Copyright 2017 Red Rabbit Games, Inc.

#include "TankAIController.h"

void ATankAIController::BeginPlay ()
{
	Super::BeginPlay ();

	auto Tank = GetControlledTank ();
	if (Tank) {
		UE_LOG (LogTemp, Warning, TEXT ("AIControlled Tank: %s"), *(Tank->GetName ()));
	}
	else {
		UE_LOG (LogTemp, Warning, TEXT ("AIController not possesing a tank"));
	}
}

ATank* ATankAIController::GetControlledTank () const
{
	return Cast<ATank> (GetPawn ());
}



