// Copyright 2017 Red Rabbit Games, Inc.

#include "../Public/Projectile.h"
#include "../Public/TankProjectileMovementComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "Components/StaticMeshComponent.h"


// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	CollisionMesh = CreateDefaultSubobject<UStaticMeshComponent> (FName ("Projectile Collision Mesh"));
	SetRootComponent (Cast<USceneComponent> (CollisionMesh));
	CollisionMesh->SetNotifyRigidBodyCollision (true);
	CollisionMesh->SetVisibility (false);

	LaunchBlast = CreateDefaultSubobject<UParticleSystemComponent> (FName ("Projectile Launch Blast"));
	LaunchBlast->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);

	ProjectileMovementComponent = CreateDefaultSubobject<UTankProjectileMovementComponent> (FName ("Projectile Movement Component"));
	ProjectileMovementComponent->bAutoActivate = false;

	ImpactBlast = CreateDefaultSubobject<UParticleSystemComponent> (FName ("Projectile Impact Blast"));
	ImpactBlast->AttachToComponent (RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	ImpactBlast->bAutoActivate = false;
}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();

	CollisionMesh->OnComponentHit.AddDynamic (this, &AProjectile::OnHit);
}

void AProjectile::OnHit (UPrimitiveComponent * HitComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, FVector NormalImpulse, const FHitResult & Hit)
{
	LaunchBlast->Deactivate ();
	ImpactBlast->Activate ();
}

void AProjectile::LaunchProjectile (float Speed)
{
	if (!ensure (ProjectileMovementComponent)) { return; }
	ProjectileMovementComponent->SetVelocityInLocalSpace (FVector::ForwardVector * Speed);
	ProjectileMovementComponent->Activate ();
}
