// Copyright 2017 Red Rabbit Games, Inc.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "TankAIController.generated.h"

/**
 * Responsible for helping the AI to move and aim
 */
UCLASS()
class SECTION_04_API ATankAIController : public AAIController
{
	GENERATED_BODY()

public:
	// Called every frame
	virtual void Tick (float DeltaTime) override;

protected:
	// How close can the AI tank get to the player
	UPROPERTY (EditDefaultsOnly, Category = "Firing")
	float AcceptanceRadius = 3000.0f; // in cm

	UPROPERTY (EditDefaultsOnly, Category = "Debug")
	bool EnableFiring = true;

private:
	virtual void SetPawn (APawn* InPawn) override;

	UFUNCTION ()
	void OnTankDeath ();
};
