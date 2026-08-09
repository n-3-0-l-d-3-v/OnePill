#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "DirectorComponent.generated.h"

class ULivingRuleAsset;
class UPlayerSignalComponent;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnLivingRuleActivated, FName, BehaviorTag);

/**
 * Evaluates the Living Rule Graph: each tick, checks every assigned ULivingRuleAsset against
 * the owner's UPlayerSignalComponent and broadcasts FOnLivingRuleActivated for rules that
 * cross their threshold. World actors subscribe to react to behavior tags — the Director
 * itself never touches world actors directly, keeping rules data-driven and decoupled.
 */
UCLASS(ClassGroup = (OnePill), meta = (BlueprintSpawnableComponent))
class ONEPILL_API UDirectorComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UDirectorComponent();

	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
		FActorComponentTickFunction* ThisTickFunction) override;

	/** Called once the swallow sequence completes; unlocks post-pill-only rules. */
	UFUNCTION(BlueprintCallable, Category = "OnePill|Director")
	void NotifyPillSwallowed();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "OnePill|Director")
	TArray<TObjectPtr<ULivingRuleAsset>> Rules;

	UPROPERTY(BlueprintAssignable, Category = "OnePill|Director")
	FOnLivingRuleActivated OnLivingRuleActivated;

protected:
	virtual void BeginPlay() override;

private:
	float GetSignalValue(const UPlayerSignalComponent* Signals, FName SignalName) const;

	TWeakObjectPtr<UPlayerSignalComponent> CachedSignals;
	bool bPillSwallowed = false;
	TSet<FName> ActiveBehaviorTags;
};
