// Copyright 2017 Red Rabbit Games, Inc.

#include "../Public/TankAimingComponent.h"
#include "Components/ActorComponent.h"
#include "Components/StaticMeshComponent.h"


// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UTankAimingComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UTankAimingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UTankAimingComponent::AimAt (FVector HitLocation)
{
	auto OurTankName = GetOwner ()->GetName ();
	FVector BarrelLocation = FVector (0.0f);
	if (Barrel) {
		BarrelLocation = Barrel->GetComponentLocation ();
	}
	UE_LOG (LogTemp, Warning, TEXT ("%s aiming at %s from %s"), *OurTankName, *(HitLocation.ToString ()), *(BarrelLocation.ToString()));
}

void UTankAimingComponent::SetBarrelReference (UStaticMeshComponent* BarrelToSet)
{
	Barrel = BarrelToSet;
}
