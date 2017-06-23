// Copyright 2017 Red Rabbit Games, Inc.

#include "../Public/TankTurret.h"
#include "Engine/World.h"


void UTankTurret::Rotate (float RelativeSpeed)
{
	RelativeSpeed = FMath::Clamp<float> (RelativeSpeed, -1.0f, 1.0f);
	auto RotationChange = RelativeSpeed * MaxDegreesPerSecond * GetWorld ()->DeltaTimeSeconds;
	auto Rotation = RelativeRotation.Yaw + RotationChange;

	SetRelativeRotation (FRotator (0.0f, Rotation, 0.0f));
}

