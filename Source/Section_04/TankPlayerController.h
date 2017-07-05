// Copyright 2017 Red Rabbit Games, Inc.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

// Forward Declarations
class UTankAimingComponent;

/**
 * Responsible for helping the player aim
 */
UCLASS()
class SECTION_04_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	// Called every frame
	virtual void Tick (float DeltaTime) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay () override;

	/// Need this do not remove even though not implemented. Get's used by BP as event!
	UFUNCTION (BlueprintImplementableEvent, Category = "Setup")
	void FoundAimingComponent (UTankAimingComponent* AimCompRef);

private:
	UPROPERTY (EditAnywhere)
	float CrossHairXLocation = 0.5f;

	UPROPERTY (EditAnywhere)
	float CrossHairYLocation = 0.33333f;

	UPROPERTY (EditAnywhere)
	float LineTraceRange = 100000.0f;

	UTankAimingComponent* AimingComponent = nullptr;

	// Start the tank moving the barrel so taht a shot wiyld hit where
	// the crosshair intersects the world
	void AimTowardsCrosshair ();

	bool GetSightRayHitLocation (FVector& OutHitLocation) const;

	FVector2D GetScreenLocation () const;

	bool GetLookVectorHitLocation (FVector& CameraLocation, FVector& LookDirection, FVector& OutHitLocation) const;

	virtual void SetPawn (APawn* InPawn) override;

	UFUNCTION ()
	void OnTankDeath ();
};
