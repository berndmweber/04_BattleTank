// Copyright 2017 Red Rabbit Games, Inc.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/NavMovementComponent.h"
#include "TankMovementComponent.generated.h"

// Forward declarations
class UTankTrack;

/**
 * Provides Tank Movement Logic
 */
UCLASS( ClassGroup = (Custom), meta = (BlueprintSpawnableComponent) )
class SECTION_04_API UTankMovementComponent : public UNavMovementComponent
{
	GENERATED_BODY ()

public:
	UFUNCTION (BlueprintCallable, Category = Input)
	void IntendMoveForward (float Throw);

	UFUNCTION (BlueprintCallable, Category = Input)
	void IntendTurnRight (float Throw);

	UFUNCTION (BlueprintCallable, Category = Setup)
	void Initialize (UTankTrack* LeftTrackToSet, UTankTrack* RightTrackToSet);

private:
	UTankTrack* LeftTrack = nullptr;
	UTankTrack* RightTrack = nullptr;
	
	// Called from the pathfinding logic by the AI controllers
	virtual void RequestDirectMove (const FVector& MoveVelocity, bool bForceMaxSpeed) override;
};
