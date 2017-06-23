// Copyright 2017 Red Rabbit Games, Inc.

#include "../Public/TankBarrel.h"


void UTankBarrel::Elevate (float RelativeSpeed)
{
	// Move the barell the right amount this frame 

	// Give a max elevation speed and the frame time
	UE_LOG (LogTemp, Warning, TEXT ("Barrel->Elevate called with relative speed %f"), RelativeSpeed);
}
