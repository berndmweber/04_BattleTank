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

private:
	// How close can the AI tank get to the player
	float AcceptanceRadius = 3000.0f; // in cm
};
