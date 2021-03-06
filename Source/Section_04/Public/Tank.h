// Copyright 2017 Red Rabbit Games, Inc.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE (FTankDelegate);

UCLASS()
class SECTION_04_API ATank : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ATank();

	virtual float TakeDamage (float DamageAmount, struct FDamageEvent const & DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;

	// Returns current health as a percentage of starting health, between 0 and 1
	UFUNCTION(BlueprintPure, Category = "Health")
	float GetHealthPercent () const;

	UPROPERTY (BlueprintAssignable, Category = "Setup")
	FTankDelegate OnDeath;

protected:
	UPROPERTY (EditDefaultsOnly, Category = "Setup")
	int32 MaxHealth = 100;
		
	UPROPERTY (VisibleAnywhere, Category = "Health")
	int32 CurrentHealth = 0;

	// Called when the game starts or when spawned
	virtual void BeginPlay () override;
};
