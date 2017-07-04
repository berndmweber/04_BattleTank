// Copyright 2017 Red Rabbit Games, Inc.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Projectile.generated.h"

// Forward declarations
class UTankProjectileMovementComponent;
class UParticleSystemComponent;

UCLASS()
class SECTION_04_API AProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProjectile();

	void LaunchProjectile (float Speed);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay () override;

private:
	UTankProjectileMovementComponent* ProjectileMovementComponent = nullptr;

	UPROPERTY(VisibleAnywhere, Category = "Firing")
	UStaticMeshComponent* CollisionMesh = nullptr;

	UPROPERTY (VisibleAnywhere, Category = "Firing")
	UParticleSystemComponent* LaunchBlast = nullptr;

	UPROPERTY (VisibleAnywhere, Category = "Firing")
	UParticleSystemComponent* ImpactBlast = nullptr;

	UFUNCTION ()
	void OnHit (UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
};
