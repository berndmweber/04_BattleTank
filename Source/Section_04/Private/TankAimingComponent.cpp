// Copyright 2017 Red Rabbit Games, Inc.

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
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void UTankAimingComponent::BeginPlay()
{
	Super::BeginPlay();
}


// Called every frame
void UTankAimingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
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
		auto TankName = GetOwner ()->GetName ();
		UE_LOG (LogTemp, Warning, TEXT ("%s aiming at %s"), *TankName, *(AimDirection.ToString ()));
	}
}

void UTankAimingComponent::SetBarrelReference (UStaticMeshComponent* BarrelToSet)
{
	Barrel = BarrelToSet;
}
