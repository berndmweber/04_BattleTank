// Copyright 2017 Red Rabbit Games, Inc.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

UCLASS()
class SECTION_04_API ATank : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ATank();

	virtual float TakeDamage (float DamageAmount, struct FDamageEvent const & DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;

protected:
	UPROPERTY (EditDefaultsOnly, Category = "Setup")
	int32 MaxHealth = 100;
		
	UPROPERTY (VisibleAnywhere, Category = "Health")
	int32 CurrentHealth = 0;
};
