// Copyright 2017 Red Rabbit Games, Inc.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

// Forward declarations
class UTankBarrel;
class AProjectile;

UCLASS()
class SECTION_04_API ATank : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ATank();

	UFUNCTION (BlueprintCallable, Category = "Setup")
	void Fire ();

private:
	// TODO this needs to be moved to the aiming component
	UPROPERTY (EditDefaultsOnly, Category = "Firing")
	float LaunchSpeed = 40000.0f;	// 1000 m/s

	UPROPERTY (EditDefaultsOnly, Category = "Firing")
	float ReloadTimeInSeconds = 3.0f;

	UPROPERTY (EditDefaultsOnly, Category = "Setup")
	TSubclassOf<AProjectile> ProjectileBlueprint;

	UTankBarrel* Barrel = nullptr; // TODO Remove

	double LastFireTime = 0.0;
};
