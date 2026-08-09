#include "Core/OnePillGameMode.h"
#include "Core/OnePillCharacter.h"

AOnePillGameMode::AOnePillGameMode()
{
	DefaultPawnClass = AOnePillCharacter::StaticClass();
}
