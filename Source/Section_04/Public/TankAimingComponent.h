// Copyright 2017 Red Rabbit Games, Inc.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"

// Forward declaration
class UTankBarrel;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SECTION_04_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTankAimingComponent();

public:
	void AimAt (FVector HitLocation, float LaunchSpeed);

	void SetBarrelReference (UTankBarrel* BarrelToSet);

	// TODO Add SetTurretReference()

private:
	UTankBarrel* Barrel = nullptr;

	void MoveBarrelTowards (FVector& AimDirection);
};
