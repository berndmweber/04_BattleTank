// Copyright 2017 Red Rabbit Games, Inc.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankTrack.generated.h"

/**
 * Holds Track's properties
 */
UCLASS( meta = (BlueprintSpawnableComponent) )
class SECTION_04_API UTankTrack : public UStaticMeshComponent
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = Input)
	void SetThrottle (float Throttle);

private:
	// This is max force per track in Newtons;
	UPROPERTY(EditDefaultsOnly)
	float TrackMaxDrivingForce = 400000.0f; // 40tons * 10m/s^2 (1g)
};
