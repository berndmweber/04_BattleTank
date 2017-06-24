// Copyright 2017 Red Rabbit Games, Inc.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

// Forward declarations
class UTankAimingComponent;
class UTankBarrel;
class UTankTurret;
class AProjectile;

UCLASS()
class SECTION_04_API ATank : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ATank();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:
	void AimAt (FVector HitLocation);

	UFUNCTION(BlueprintCallable, Category = Setup)
	void SetBarrelReference (UTankBarrel* BarrelToSet);

	UFUNCTION (BlueprintCallable, Category = Setup)
	void SetTurretReference (UTankTurret* TurretToSet);

	UFUNCTION (BlueprintCallable, Category = Setup)
	void Fire ();

protected:
	UTankAimingComponent* TankAimingComponent = nullptr;

private:
	UPROPERTY (EditDefaultsOnly, Category = Firing)
	float LaunchSpeed = 100000.0f;	// 1000 m/s

	UPROPERTY (EditDefaultsOnly, Category = Firing)
	float ReloadTimeInSeconds = 3.0f;

	UPROPERTY (EditDefaultsOnly, Category = Setup)
	TSubclassOf<AProjectile> ProjectileBlueprint;

	UTankBarrel* Barrel = nullptr;

	double LastFireTime = 0.0;
};
