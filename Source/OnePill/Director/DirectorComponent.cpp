#include "Director/DirectorComponent.h"
#include "Director/LivingRuleAsset.h"
#include "Signals/PlayerSignalComponent.h"

UDirectorComponent::UDirectorComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UDirectorComponent::BeginPlay()
{
	Super::BeginPlay();

	if (const AActor* Owner = GetOwner())
	{
		CachedSignals = Owner->FindComponentByClass<UPlayerSignalComponent>();
	}
}

void UDirectorComponent::NotifyPillSwallowed()
{
	bPillSwallowed = true;
}

float UDirectorComponent::GetSignalValue(const UPlayerSignalComponent* Signals, FName SignalName) const
{
	if (!Signals)
	{
		return 0.f;
	}

	if (SignalName == TEXT("MovementSpeed"))
	{
		return Signals->GetNormalizedMovementSpeed();
	}
	if (SignalName == TEXT("Stillness"))
	{
		// Stillness duration is unbounded seconds; normalize against a 5s reference.
		return FMath::Clamp(Signals->GetStillnessDuration() / 5.f, 0.f, 1.f);
	}

	return 0.f;
}

void UDirectorComponent::TickComponent(float DeltaTime, ELevelTick TickType,
	FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	const UPlayerSignalComponent* Signals = CachedSignals.Get();
	if (!Signals)
	{
		return;
	}

	for (const ULivingRuleAsset* Rule : Rules)
	{
		if (!Rule || (Rule->bRequiresPostPill && !bPillSwallowed))
		{
			continue;
		}

		const float SignalValue = GetSignalValue(Signals, Rule->SignalName);
		const bool bShouldBeActive = SignalValue >= Rule->ActivationThreshold;
		const bool bIsActive = ActiveBehaviorTags.Contains(Rule->BehaviorTag);

		if (bShouldBeActive && !bIsActive)
		{
			ActiveBehaviorTags.Add(Rule->BehaviorTag);
			OnLivingRuleActivated.Broadcast(Rule->BehaviorTag);
		}
		else if (!bShouldBeActive && bIsActive)
		{
			ActiveBehaviorTags.Remove(Rule->BehaviorTag);
		}
	}
}
