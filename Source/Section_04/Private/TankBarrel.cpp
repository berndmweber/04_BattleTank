// Copyright 2017 Red Rabbit Games, Inc.

#include "../Public/TankBarrel.h"
#include "Engine/World.h"


void UTankBarrel::Elevate (float RelativeSpeed)
{
	// Move the barell the right amount this frame 
	// Give a max elevation speed and the frame time
	RelativeSpeed = FMath::Clamp<float> (RelativeSpeed, -1.0f, 1.0f);
	auto ElevationChange = RelativeSpeed * MaxDegreesPerSecond * GetWorld ()->DeltaTimeSeconds;
	auto Elevation = RelativeRotation.Pitch + ElevationChange;

	Elevation = FMath::Clamp<float> (Elevation, MinElevationDegrees, MaxElevationDegrees);

	SetRelativeRotation (FRotator (Elevation, 0.0f, 0.0f));
}
