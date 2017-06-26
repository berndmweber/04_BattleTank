// Copyright 2017 Red Rabbit Games, Inc.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Projectile.generated.h"

// Forward declarations
class UTankProjectileMovementComponent;

UCLASS()
class SECTION_04_API AProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProjectile();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void LaunchProjectile (float Speed);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay () override;

private:
	UTankProjectileMovementComponent* ProjectileMovementComponent = nullptr;
};
