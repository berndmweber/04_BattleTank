// Copyright 2017 Red Rabbit Games, Inc.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"

// Forward declaration
class UTankBarrel;
class UTankTurret;
class AProjectile;

// Enum for aiming state
UENUM()
enum class EFiringState : uint8
{
	Reloading,
	Aiming,
	Locked,
	OutOfAmmo
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SECTION_04_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTankAimingComponent();

	void AimAt (FVector HitLocation);

	UFUNCTION (BlueprintCallable, Category = "Setup")
	void Initialize (UTankBarrel* BarrelToSet, UTankTurret* TurretToSet);

	UFUNCTION (BlueprintCallable, Category = "Setup")
	void Fire ();

	EFiringState GetFiringState () const;

	UFUNCTION (BlueprintCallable, Category = "Firing")
	int32 GetAmmo () const;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay () override;

	UPROPERTY (BlueprintReadOnly, Category = "State")
	EFiringState FiringState = EFiringState::Reloading;

	UPROPERTY (EditDefaultsOnly, Category = "Firing")
	int32 Ammo = 3;

private:
	UPROPERTY (EditDefaultsOnly, Category = "Firing")
	float LaunchSpeed = 40000.0f;	// 1000 m/s

	UPROPERTY (EditDefaultsOnly, Category = "Firing")
	float ReloadTimeInSeconds = 3.0f;

	UPROPERTY (EditDefaultsOnly, Category = "Setup")
	TSubclassOf<AProjectile> ProjectileBlueprint;

	double LastFireTime = 0.0;

	UTankBarrel* Barrel = nullptr;
	UTankTurret* Turret = nullptr;

	FVector AimDirection;

	virtual void TickComponent (float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;

	void MoveBarrelTowards (FVector& AimDirection);
	void MoveTurretTowards (FVector& AimDirection);

	bool IsBarrelMoving ();
};
