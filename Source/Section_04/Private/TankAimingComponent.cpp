// Copyright 2017 Red Rabbit Games, Inc.

#include "../Public/TankAimingComponent.h"
#include "../Public/TankBarrel.h"
#include "../Public/TankTurret.h"
#include "Components/ActorComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"

// output parameter
#define OUT

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
}

void UTankAimingComponent::AimAt (FVector HitLocation, float LaunchSpeed)
{
	if (!Barrel) { return; }

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
		auto AimDirection = LaunchVelocity.GetSafeNormal ();
		MoveBarrelTowards (AimDirection);
		MoveTurretTowards (AimDirection);
	}
	else {
		auto Time = GetWorld ()->GetTimeSeconds ();
		UE_LOG (LogTemp, Warning, TEXT ("%f - No aim solution found."), Time);
	}
	// No target solution; do nothing
}

void UTankAimingComponent::SetBarrelReference (UTankBarrel* BarrelToSet)
{
	if (!BarrelToSet) { return; }
	Barrel = BarrelToSet;
}

void UTankAimingComponent::SetTurretReference (UTankTurret * TurretToSet)
{
	if (!TurretToSet) { return; }
	Turret = TurretToSet;
}

void UTankAimingComponent::MoveBarrelTowards (FVector& AimDirection)
{
	// Work out difference between current barrel location and aim direction
	auto BarrelRotator = Barrel->GetForwardVector ().Rotation ();
	auto AimAsARotator = AimDirection.Rotation ();
	auto DeltaRotator = AimAsARotator - BarrelRotator;

	Barrel->Elevate (DeltaRotator.Pitch);
}

void UTankAimingComponent::MoveTurretTowards (FVector & AimDirection)
{
	// Work out difference between current barrel location and aim direction
	auto TurretRotator = Turret->GetForwardVector ().Rotation ();
	auto AimAsARotator = AimDirection.Rotation ();
	auto DeltaRotator = AimAsARotator - TurretRotator;

	Turret->Rotate (DeltaRotator.Yaw);
}
