#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SwallowTrigger.generated.h"

class USphereComponent;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnSwallowed);

/**
 * Placed in the Pre-Pill level at the point of no return. When the player interacts with it,
 * fires the swallow sequence and notifies the Director that post-pill rules may now activate.
 * This is the one boundary in the whole experience that cannot be undone.
 */
UCLASS()
class ONEPILL_API ASwallowTrigger : public AActor
{
	GENERATED_BODY()

public:
	ASwallowTrigger();

	/** Called by player interaction logic (e.g. an interact input) once, and only once. */
	UFUNCTION(BlueprintCallable, Category = "OnePill|SwallowSequence")
	void Swallow(APawn* InstigatorPawn);

	UPROPERTY(BlueprintAssignable, Category = "OnePill|SwallowSequence")
	FOnSwallowed OnSwallowed;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "OnePill|SwallowSequence")
	TObjectPtr<USphereComponent> InteractionSphere;

private:
	bool bHasBeenSwallowed = false;
};
