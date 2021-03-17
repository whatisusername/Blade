#include "BladeGameModeBase.h"
#include "BladeCharacterBase.h"
#include "BladeGameStateBase.h"
#include "BladePlayerControllerBase.h"

ABladeGameModeBase::ABladeGameModeBase()
{
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawn(TEXT("/Game/Blueprints/BP_PlayerCharacter"));
	DefaultPawnClass = PlayerPawn.Class;
	
	GameStateClass = ABladeGameStateBase::StaticClass();
	PlayerControllerClass = ABladePlayerControllerBase::StaticClass();
}
