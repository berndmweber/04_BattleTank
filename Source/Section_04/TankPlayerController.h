// Copyright 2017 Red Rabbit Games, Inc.

#pragma once

#include "Public/Tank.h"
#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class SECTION_04_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay () override;

public:
	// Called every frame
	virtual void Tick (float DeltaTime) override;

private:
	ATank* GetControlledTank () const;

	// Start the tank moving the barrel so taht a shot wiyld hit where
	// the crosshair intersects the world
	void AimTowardsCrosshair ();

};
