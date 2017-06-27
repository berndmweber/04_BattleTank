// Copyright 2017 Red Rabbit Games, Inc.

#include "../Public/Tank.h"
#include "../Public/Projectile.h"
#include "../Public/TankAimingComponent.h"
#include "../Public/TankBarrel.h"
#include "Engine/World.h"

// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

// Called when the game starts or when spawned
void ATank::BeginPlay ()
{
	Super::BeginPlay ();

	TankAimingComponent = FindComponentByClass<UTankAimingComponent> (); // TODO Need to get rid of this -> for AimAt
}

void ATank::AimAt (FVector HitLocation)
{
	if (!ensure (TankAimingComponent)) { return; }
	TankAimingComponent->AimAt (HitLocation, LaunchSpeed);
}

void ATank::Fire (void)
{
	if (!ensure (Barrel)) { return; }

	if ((FPlatformTime::Seconds () - LastFireTime) > ReloadTimeInSeconds) {
		// Spawn a projectile at the socker location on the barrel
		auto Projectile = GetWorld ()->SpawnActor<AProjectile> (
			ProjectileBlueprint,
			Barrel->GetSocketLocation (FName ("Projectile")),
			Barrel->GetSocketRotation (FName ("Projectile"))
			);
		if (ensure(Projectile)) {
			Projectile->LaunchProjectile (LaunchSpeed);
			LastFireTime = FPlatformTime::Seconds ();
		}
	}
}
