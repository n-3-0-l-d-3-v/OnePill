#include "Signals/PlayerSignalComponent.h"
#include "GameFramework/Pawn.h"
#include "Camera/CameraComponent.h"

UPlayerSignalComponent::UPlayerSignalComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	PrimaryComponentTick.TickGroup = TG_PostUpdateWork;
}

void UPlayerSignalComponent::BeginPlay()
{
	Super::BeginPlay();

	if (const AActor* Owner = GetOwner())
	{
		LastLocation = Owner->GetActorLocation();
	}
}

void UPlayerSignalComponent::TickComponent(float DeltaTime, ELevelTick TickType,
	FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	const APawn* OwnerPawn = Cast<APawn>(GetOwner());
	if (!OwnerPawn || DeltaTime <= 0.f)
	{
		return;
	}

	if (const UCameraComponent* Camera = OwnerPawn->FindComponentByClass<UCameraComponent>())
	{
		GazeDirection = Camera->GetForwardVector();
	}

	const FVector CurrentLocation = OwnerPawn->GetActorLocation();
	const float Speed = FVector::Dist(CurrentLocation, LastLocation) / DeltaTime;
	LastLocation = CurrentLocation;

	NormalizedMovementSpeed = FMath::Clamp(Speed / MaxObservedSpeed, 0.f, 1.f);

	if (Speed < StillnessSpeedThreshold)
	{
		StillnessDuration += DeltaTime;
	}
	else
	{
		StillnessDuration = 0.f;
	}
}
