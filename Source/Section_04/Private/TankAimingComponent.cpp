// Copyright 2017 Red Rabbit Games, Inc.

#include "../Public/TankBarrel.h"
#include "../Public/TankAimingComponent.h"
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
	PrimaryComponentTick.bCanEverTick = false; // TODO Should this tick?
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
			ESuggestProjVelocityTraceOption::TraceFullPath) // TODO: Turn this off id trace is not needed anymore
		)
	{
		auto AimDirection = LaunchVelocity.GetSafeNormal ();
		MoveBarrelTowards (AimDirection);
	}
	else {
		UE_LOG (LogTemp, Warning, TEXT ("No aim solution found."));
	}
	// No target solution; do nothing
}

void UTankAimingComponent::SetBarrelReference (UTankBarrel* BarrelToSet)
{
	Barrel = BarrelToSet;
}

void UTankAimingComponent::MoveBarrelTowards (FVector& AimDirection)
{
	// Work out difference between current barrel location and aim direction
	auto BarrelRotator = Barrel->GetForwardVector ().Rotation ();
	auto AimAsARotator = AimDirection.Rotation ();
	auto DeltaRotator = AimAsARotator - BarrelRotator;

	UE_LOG (LogTemp, Warning, TEXT ("AimAsRotator: %s"), *(AimAsARotator.ToString ()));

	Barrel->Elevate (5.0f); // TODO remove magic number
}
