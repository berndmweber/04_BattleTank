// Copyright 2017 Red Rabbit Games, Inc.

#include "../Public/TankBarrel.h"
#include "Engine/World.h"


void UTankBarrel::Elevate (float RelativeSpeed)
{
	// Move the barell the right amount this frame 

	// Give a max elevation speed and the frame time
	auto Time = GetWorld ()->GetTimeSeconds ();
	UE_LOG (LogTemp, Warning, TEXT ("%f - Barrel->Elevate called with relative speed %f"), Time, RelativeSpeed);
}
