// Copyright 2017 Red Rabbit Games, Inc.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SECTION_04_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTankAimingComponent();

public:
	void AimAt (FVector HitLocation, float LaunchSpeed);

	void SetBarrelReference (UStaticMeshComponent* BarrelToSet);

	// TODO Add SetTurretReference()

private:
	UStaticMeshComponent* Barrel = nullptr;

	void MoveBarrelTowards (FVector& AimDirection);
};
