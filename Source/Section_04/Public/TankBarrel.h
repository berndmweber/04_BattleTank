// Copyright 2017 Red Rabbit Games, Inc.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankBarrel.generated.h"

/**
 * Holds Barrel's properties
 */
UCLASS( meta = (BlueprintSpawnableComponent) )
class SECTION_04_API UTankBarrel : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:
	// -1 is max downward movement, and +1 is max up movement
	void Elevate (float RelativeSpeed);

private:
	UPROPERTY (EditDefaultsOnly, Category = "Setup")
	float MaxDegreesPerSecond = 5.0f;

	UPROPERTY (EditDefaultsOnly, Category = "Setup")
	float MaxElevationDegrees = 40.0f;

	UPROPERTY (EditDefaultsOnly, Category = "Setup")
	float MinElevationDegrees = 0.0f;
};
