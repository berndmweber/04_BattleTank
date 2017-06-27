// Copyright 2017 Red Rabbit Games, Inc.

#include "../Public/TankAIController.h"
#include "../Public/TankAimingComponent.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"

void ATankAIController::Tick (float DeltaTime)
{
	Super::Tick (DeltaTime);

	auto ControlledTank = GetPawn ();
	if (ensure (ControlledTank)) {
		auto PlayerTank = GetWorld ()->GetFirstPlayerController ()->GetPawn ();
		UTankAimingComponent* AimingComponent = ControlledTank->FindComponentByClass<UTankAimingComponent> ();

		if (ensure (PlayerTank && AimingComponent)) {
			// Move towards player
			MoveToActor (PlayerTank, AcceptanceRadius);

			// Aim towards player and fire
			AimingComponent->AimAt (PlayerTank->GetActorLocation ());

			// TODO Fix firing
			//ControlledTank->Fire ();
		}
	}
}
