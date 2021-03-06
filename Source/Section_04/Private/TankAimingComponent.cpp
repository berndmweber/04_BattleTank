// Copyright 2017 Red Rabbit Games, Inc.

#include "../Public/TankAimingComponent.h"
#include "../Public/TankBarrel.h"
#include "../Public/TankTurret.h"
#include "../Public/Projectile.h"
#include "Components/ActorComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"

// output parameter
#define OUT

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent ()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void UTankAimingComponent::BeginPlay ()
{
	Super::BeginPlay ();

	// So that the first fire is after an initial reload
	LastFireTime = FPlatformTime::Seconds ();
}

void UTankAimingComponent::AimAt (FVector HitLocation)
{
	if (!ensure (Barrel && Turret)) { return; }

	FVector LaunchVelocity;
	FVector StartLocation = Barrel->GetSocketLocation (FName ("Projectile"));

	// Calculate the launch velocity
	if (UGameplayStatics::SuggestProjectileVelocity (
			this,
			OUT LaunchVelocity,
			StartLocation,
			HitLocation,
			LaunchSpeed,
			false,
			0.0f,
			0.0f,
			ESuggestProjVelocityTraceOption::DoNotTrace) // Using something else will likely cause the solution to be dropped
		)
	{
		AimDirection = LaunchVelocity.GetSafeNormal ();
		MoveBarrelTowards (AimDirection);
		MoveTurretTowards (AimDirection);
	}
}

void UTankAimingComponent::Initialize (UTankBarrel* BarrelToSet, UTankTurret* TurretToSet)
{
	Barrel = BarrelToSet;
	Turret = TurretToSet;
}

void UTankAimingComponent::TickComponent (float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
	Super::TickComponent (DeltaTime, TickType, ThisTickFunction);

	if (GetAmmo () <= 0) {
		FiringState = EFiringState::OutOfAmmo;
	} else if ((FPlatformTime::Seconds () - LastFireTime) < ReloadTimeInSeconds) {
		FiringState = EFiringState::Reloading;
	}
	else if (IsBarrelMoving ()) {
		FiringState = EFiringState::Aiming;
	}
	else {
		FiringState = EFiringState::Locked;
	}
}

EFiringState UTankAimingComponent::GetFiringState () const
{
	return FiringState;
}

int32 UTankAimingComponent::GetAmmo () const
{
	return Ammo;
}

bool UTankAimingComponent::IsBarrelMoving ()
{
	if (!ensure (Barrel)) { return false; }
	auto BarrelForward = Barrel->GetForwardVector ();
	// TODO The Tolerance here is larger than anticipated. For some reason the Barrel and the aimdirection diverge quite a bit...
	return !BarrelForward.Equals (AimDirection, 0.15f);
}

void UTankAimingComponent::MoveBarrelTowards (FVector& AimDirection)
{
	if (!ensure (Barrel)) { return; }
	// Work out difference between current barrel location and aim direction
	auto BarrelRotator = Barrel->GetForwardVector ().Rotation ();
	auto AimAsARotator = AimDirection.Rotation ();
	auto DeltaRotator = AimAsARotator - BarrelRotator;

	Barrel->Elevate (DeltaRotator.Pitch);
}

void UTankAimingComponent::MoveTurretTowards (FVector& AimDirection)
{
	if (!ensure (Turret)) { return; }
	// Work out difference between current barrel location and aim direction
	auto TurretRotator = Turret->GetForwardVector ().Rotation ();
	auto AimAsARotator = AimDirection.Rotation ();
	auto DeltaRotator = AimAsARotator - TurretRotator;

	// Always yaw the shortest way
	if (FMath::Abs<float> (DeltaRotator.Yaw) < 180) {
		Turret->Rotate (DeltaRotator.Yaw);
	}
	else {
		Turret->Rotate (-DeltaRotator.Yaw);
	}
}

void UTankAimingComponent::Fire (void)
{
	if (!ensure (Barrel && ProjectileBlueprint)) { return; }

	if ((FiringState == EFiringState::Locked) || (FiringState == EFiringState::Aiming)) {
		// Spawn a projectile at the socker location on the barrel
		auto Projectile = GetWorld ()->SpawnActor<AProjectile> (
			ProjectileBlueprint,
			Barrel->GetSocketLocation (FName ("Projectile")),
			Barrel->GetSocketRotation (FName ("Projectile"))
			);
		if (ensure (Projectile)) {
			Projectile->LaunchProjectile (LaunchSpeed);
			LastFireTime = FPlatformTime::Seconds ();
			Ammo--;
		}
	}
}
