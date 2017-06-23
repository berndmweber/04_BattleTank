// Copyright 2017 Red Rabbit Games, Inc.

#include "../Public/Tank.h"
#include "../Public/TankBarrel.h"
#include "../Public/TankTurret.h"
#include "../Public/TankAimingComponent.h"


// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	// No need to protect pointers as added at construction
	TankAimingComponent = CreateDefaultSubobject<UTankAimingComponent> (FName ("Aiming Component"));
}

void ATank::AimAt (FVector HitLocation)
{
	TankAimingComponent->AimAt (HitLocation, LaunchSpeed);
}

void ATank::SetBarrelReference (UTankBarrel* BarrelToSet)
{
	TankAimingComponent->SetBarrelReference (BarrelToSet);
}

void ATank::SetTurretReference (UTankTurret* TurretToSet)
{
	TankAimingComponent->SetTurretReference (TurretToSet);
}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();
}

// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}
