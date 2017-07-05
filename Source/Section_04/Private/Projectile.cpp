// Copyright 2017 Red Rabbit Games, Inc.

#include "../Public/Projectile.h"
#include "../Public/TankProjectileMovementComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "Components/StaticMeshComponent.h"
#include "PhysicsEngine/RadialForceComponent.h"
#include "Engine/World.h"
#include "TimerManager.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/DamageType.h"


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

	ExplosionForce = CreateDefaultSubobject<URadialForceComponent> (FName ("Projectile Explosion Force"));
	ExplosionForce->AttachToComponent (RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
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
	ExplosionForce->FireImpulse ();

	SetRootComponent (ImpactBlast);
	CollisionMesh->DestroyComponent ();

	UGameplayStatics::ApplyRadialDamage (
		this,
		ProjectileDamage,
		GetActorLocation(),
		ExplosionForce->Radius, // For consistency
		UDamageType::StaticClass(),
		TArray<AActor*>() // Damage all actors
	);

	FTimerHandle TimerHandle;
	GetWorld ()->GetTimerManager ().SetTimer (TimerHandle, this, &AProjectile::OnTimerExpire, DestroyDelay, false);
}

void AProjectile::OnTimerExpire ()
{
	this->Destroy ();
}

void AProjectile::LaunchProjectile (float Speed)
{
	if (!ensure (ProjectileMovementComponent)) { return; }
	ProjectileMovementComponent->SetVelocityInLocalSpace (FVector::ForwardVector * Speed);
	ProjectileMovementComponent->Activate ();
}
