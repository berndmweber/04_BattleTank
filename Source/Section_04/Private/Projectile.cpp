// Copyright 2017 Red Rabbit Games, Inc.

#include "../Public/Projectile.h"
#include "../Public/TankProjectileMovementComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "Components/StaticMeshComponent.h"


// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CollisionMesh = CreateDefaultSubobject<UStaticMeshComponent> (FName ("Projectile Collision Mesh"));
	SetRootComponent (Cast<USceneComponent> (CollisionMesh));
	CollisionMesh->SetNotifyRigidBodyCollision (true);
	CollisionMesh->SetVisibility (false);

	LaunchBlast = CreateDefaultSubobject<UParticleSystemComponent> (FName ("Projectile Launch Blast"));
	LaunchBlast->AttachTo (RootComponent);

	ProjectileMovementComponent = CreateDefaultSubobject<UTankProjectileMovementComponent> (FName ("Projectile Movement Component"));
	ProjectileMovementComponent->bAutoActivate = false;
}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AProjectile::LaunchProjectile (float Speed)
{
	if (!ensure (ProjectileMovementComponent)) { return; }
	ProjectileMovementComponent->SetVelocityInLocalSpace (FVector::ForwardVector * Speed);
	ProjectileMovementComponent->Activate ();
}
