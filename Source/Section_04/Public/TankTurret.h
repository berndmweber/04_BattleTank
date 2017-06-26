// Copyright 2017 Red Rabbit Games, Inc.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankTurret.generated.h"

/**
 * Holds turret's properties
 */
UCLASS( meta = (BlueprintSpawnableComponent) )
class SECTION_04_API UTankTurret : public UStaticMeshComponent
{
	GENERATED_BODY()

public:
	// -1 is max left movement, and +1 is max right movement
	void Rotate (float RelativeSpeed);

private:
	UPROPERTY (EditDefaultsOnly, Category = "Setup")
	float MaxDegreesPerSecond = 20.0f;
};
