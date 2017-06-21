// Copyright 2017 Red Rabbit Games, Inc.

#pragma once

#include "Tank.h"
#include "CoreMinimal.h"
#include "AIController.h"
#include "TankAIController.generated.h"

/**
 * 
 */
UCLASS()
class SECTION_04_API ATankAIController : public AAIController
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay () override;

private:
	ATank* GetControlledTank () const;

	ATank* GetPlayerTank () const;

};
