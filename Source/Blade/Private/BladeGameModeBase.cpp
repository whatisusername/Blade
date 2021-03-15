#include "BladeGameModeBase.h"
#include "BladeCharacterBase.h"
#include "BladeGameStateBase.h"
#include "BladePlayerControllerBase.h"

ABladeGameModeBase::ABladeGameModeBase()
{
	GameStateClass = ABladeGameStateBase::StaticClass();
	DefaultPawnClass = ABladeCharacterBase::StaticClass();
	PlayerControllerClass = ABladePlayerControllerBase::StaticClass();
}
