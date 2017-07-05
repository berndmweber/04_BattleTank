// Copyright 2017 Red Rabbit Games, Inc.

#include "../Public/Tank.h"

// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

void ATank::BeginPlay ()
{
	Super::BeginPlay ();

	CurrentHealth = MaxHealth;
}

float ATank::TakeDamage (float DamageAmount, FDamageEvent const & DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	int32 DamagePoints = FPlatformMath::RoundToInt (DamageAmount);
	int32 DamageToApply = FMath::Clamp<int32> (DamagePoints, 0, MaxHealth);

	CurrentHealth -= DamageToApply;
	if (CurrentHealth <= 0) {
		OnDeath.Broadcast ();
	}

	return (float)DamageToApply;
}

float ATank::GetHealthPercent () const
{
	return (float)CurrentHealth / (float)MaxHealth;
}
