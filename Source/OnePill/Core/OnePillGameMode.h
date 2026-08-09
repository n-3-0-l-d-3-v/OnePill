#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "OnePillGameMode.generated.h"

/**
 * Game mode for the Pre-Pill sequence: normal first-person controls, no living-system
 * behaviors active yet.
 */
UCLASS()
class ONEPILL_API AOnePillGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AOnePillGameMode();
};
