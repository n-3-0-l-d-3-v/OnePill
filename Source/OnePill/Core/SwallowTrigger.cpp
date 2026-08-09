#include "Core/SwallowTrigger.h"
#include "Components/SphereComponent.h"
#include "Director/DirectorComponent.h"

ASwallowTrigger::ASwallowTrigger()
{
	InteractionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("InteractionSphere"));
	InteractionSphere->InitSphereRadius(64.f);
	RootComponent = InteractionSphere;
}

void ASwallowTrigger::Swallow(APawn* InstigatorPawn)
{
	if (bHasBeenSwallowed || !InstigatorPawn)
	{
		return;
	}

	bHasBeenSwallowed = true;

	if (UDirectorComponent* Director = InstigatorPawn->FindComponentByClass<UDirectorComponent>())
	{
		Director->NotifyPillSwallowed();
	}

	OnSwallowed.Broadcast();
}
