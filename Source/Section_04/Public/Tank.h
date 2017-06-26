// Copyright 2017 Red Rabbit Games, Inc.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

// Forward declarations
class UTankAimingComponent;
class UTankBarrel;
class AProjectile;

UCLASS()
class SECTION_04_API ATank : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ATank();

	void AimAt (FVector HitLocation);

	UFUNCTION (BlueprintCallable, Category = "Setup")
	void Fire ();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay () override;

	UPROPERTY (BlueprintReadOnly)
	UTankAimingComponent* TankAimingComponent = nullptr;

private:
	UPROPERTY (EditDefaultsOnly, Category = "Firing")
	float LaunchSpeed = 100000.0f;	// 1000 m/s

	UPROPERTY (EditDefaultsOnly, Category = "Firing")
	float ReloadTimeInSeconds = 3.0f;

	UPROPERTY (EditDefaultsOnly, Category = "Setup")
	TSubclassOf<AProjectile> ProjectileBlueprint;

	UTankBarrel* Barrel = nullptr; // TODO Remove

	double LastFireTime = 0.0;
};
