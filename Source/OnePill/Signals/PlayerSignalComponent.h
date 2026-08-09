#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PlayerSignalComponent.generated.h"

/**
 * Captures raw player behavior (gaze, movement speed, stillness) and exposes it as normalized
 * signals for the Living Rule Graph, adaptive music engine, and gaze-contingent resolution
 * system to consume. This component only observes — it never modifies gameplay itself.
 */
UCLASS(ClassGroup = (OnePill), meta = (BlueprintSpawnableComponent))
class ONEPILL_API UPlayerSignalComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UPlayerSignalComponent();

	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
		FActorComponentTickFunction* ThisTickFunction) override;

	/** Current forward gaze direction, world space. */
	UFUNCTION(BlueprintPure, Category = "OnePill|Signals")
	FVector GetGazeDirection() const { return GazeDirection; }

	/** Movement speed normalized 0-1 against MaxObservedSpeed. */
	UFUNCTION(BlueprintPure, Category = "OnePill|Signals")
	float GetNormalizedMovementSpeed() const { return NormalizedMovementSpeed; }

	/** Seconds the player has been continuously still (below StillnessSpeedThreshold). */
	UFUNCTION(BlueprintPure, Category = "OnePill|Signals")
	float GetStillnessDuration() const { return StillnessDuration; }

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, Category = "OnePill|Signals")
	float MaxObservedSpeed = 600.f;

	UPROPERTY(EditDefaultsOnly, Category = "OnePill|Signals")
	float StillnessSpeedThreshold = 5.f;

private:
	FVector GazeDirection = FVector::ForwardVector;
	float NormalizedMovementSpeed = 0.f;
	float StillnessDuration = 0.f;
	FVector LastLocation = FVector::ZeroVector;
};
