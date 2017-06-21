// Copyright 2017 Red Rabbit Games, Inc.

#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
#include "../Public/TankAIController.h"

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
	Tank = GetPlayerTank ();
	if (Tank) {
		UE_LOG (LogTemp, Warning, TEXT ("PlayerTank found: %s!"), *(Tank->GetName ()));
	}
	else {
		UE_LOG (LogTemp, Warning, TEXT ("No PlayerTank found"));
	}

}

ATank* ATankAIController::GetControlledTank () const
{
	return Cast<ATank> (GetPawn ());
}

ATank * ATankAIController::GetPlayerTank () const
{
	return Cast<ATank> (GetWorld ()->GetFirstPlayerController ()->GetPawn ());
}



