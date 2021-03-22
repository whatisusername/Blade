#include "BladeGameModeBase.h"
#include "BladeGameStateBase.h"
#include "Kismet/GameplayStatics.h"

ABladeGameModeBase::ABladeGameModeBase()
{
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawn(TEXT("/Game/Blueprints/BP_PlayerCharacter"));
	DefaultPawnClass = PlayerPawn.Class;

	static ConstructorHelpers::FClassFinder<APlayerController> PlayerController(TEXT("/Game/Blueprints/BP_PlayerController"));
	PlayerControllerClass = PlayerController.Class;

	GameStateClass = ABladeGameStateBase::StaticClass();
}

void ABladeGameModeBase::GameOver()
{
	UGameplayStatics::SetGlobalTimeDilation(GetWorld(), 0.25f);

	FTimerDelegate TimerCallback;
	TimerCallback.BindLambda([this]()
	{
		UGameplayStatics::SetGlobalTimeDilation(GetWorld(), 1.0f);
		UGameplayStatics::SetGamePaused(GetWorld(), true);
	});

	GetWorldTimerManager().SetTimer(TimerHandle, TimerCallback, 1.5f, false);
}
