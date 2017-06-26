// Copyright 2017 Red Rabbit Games, Inc.

#include "../Public/TankAIController.h"
#include "../Public/Tank.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"

void ATankAIController::Tick (float DeltaTime)
{
	Super::Tick (DeltaTime);

	ATank* PlayerTank = Cast<ATank> (GetWorld ()->GetFirstPlayerController ()->GetPawn ());
	ATank* ControlledTank = Cast<ATank> (GetPawn ());

	if (ensure (PlayerTank && ControlledTank)) {
		// Move towards player
		MoveToActor (PlayerTank, AcceptanceRadius);

		// Aim towards player and fire
		ControlledTank->AimAt (PlayerTank->GetActorLocation ());
		ControlledTank->Fire ();
	}
}

void ATankAIController::BeginPlay ()
{
	Super::BeginPlay ();
}
