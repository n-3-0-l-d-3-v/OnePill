#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "LivingRuleAsset.generated.h"

/**
 * A single data-driven rule the Director can activate post-pill: which signal it reads,
 * the threshold that triggers it, and a tag identifying the world behavior it turns on.
 * Designers author these as data assets instead of the rule logic being hardcoded in C++.
 */
UCLASS(BlueprintType)
class ONEPILL_API ULivingRuleAsset : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	/** Human-readable name for designers, e.g. "Stillness blooms the ceiling". */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "OnePill|Director")
	FText RuleName;

	/** Which player signal this rule listens to (matches a field on UPlayerSignalComponent). */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "OnePill|Director")
	FName SignalName;

	/** Normalized threshold (0-1) the signal must cross to activate this rule. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "OnePill|Director",
		meta = (ClampMin = "0.0", ClampMax = "1.0"))
	float ActivationThreshold = 0.5f;

	/** Gameplay tag / identifier broadcast to listening world actors when this rule activates. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "OnePill|Director")
	FName BehaviorTag;

	/** Only evaluated once the player has swallowed the pill. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "OnePill|Director")
	bool bRequiresPostPill = true;
};
