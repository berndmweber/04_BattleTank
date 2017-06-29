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
	UTankTrack ();

	UFUNCTION(BlueprintCallable, Category = "Input")
	void SetThrottle (float Throttle);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay () override;

private:
	// This is max force per track in Newtons;
	UPROPERTY(EditDefaultsOnly)
	float TrackMaxDrivingForce = 400000.0f; // 40tons * 10m/s^2 (1g)

	float MaxThrottle = 1.0f;
	float MinThrottle = -1.0f;

	virtual void TickComponent (float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;

	UFUNCTION ()
	void OnHit (UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
};
