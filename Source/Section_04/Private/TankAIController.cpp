// Copyright 2017 Red Rabbit Games, Inc.

#include "../Public/TankAIController.h"
#include "../Public/TankAimingComponent.h"
#include "../Public/Tank.h"
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

			// If aim or locked
			if (AimingComponent->GetFiringState () == EFiringState::Locked) {
				if (EnableFiring) {
					AimingComponent->Fire ();
				}
			}
		}
	}
}

void ATankAIController::SetPawn (APawn* InPawn)
{
	Super::SetPawn (InPawn);

	if (ensure (InPawn)) {
		auto PossessedTank = Cast<ATank> (InPawn);

		// Subscribe our local method to the tank's death event
		PossessedTank->OnDeath.AddUniqueDynamic (this, &ATankAIController::OnTankDeath);
	}
}

void ATankAIController::OnTankDeath ()
{
	if (!ensure (GetPawn ())) { return; } // TODO remove ensure
	GetPawn()->DetachFromControllerPendingDestroy ();
}
