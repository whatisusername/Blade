#include "BladeGameModeBase.h"
#include "BladeGameStateBase.h"

ABladeGameModeBase::ABladeGameModeBase()
{
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawn(TEXT("/Game/Blueprints/BP_PlayerCharacter"));
	DefaultPawnClass = PlayerPawn.Class;

	static ConstructorHelpers::FClassFinder<APlayerController> PlayerController(TEXT("/Game/Blueprints/BP_PlayerController"));
	PlayerControllerClass = PlayerController.Class;

	GameStateClass = ABladeGameStateBase::StaticClass();
}
