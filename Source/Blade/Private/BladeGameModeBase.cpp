#include "BladeGameModeBase.h"
#include "BladeGameFinishWidget.h"
#include "BladeGameStateBase.h"
#include "BladePlayerControllerBase.h"
#include "Blueprint/UserWidget.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Kismet/GameplayStatics.h"

ABladeGameModeBase::ABladeGameModeBase()
{
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawn(TEXT("/Game/Blueprints/BP_PlayerCharacter"));
	DefaultPawnClass = PlayerPawn.Class;

	static ConstructorHelpers::FClassFinder<APlayerController> PlayerController(TEXT("/Game/Blueprints/BP_PlayerController"));
	PlayerControllerClass = PlayerController.Class;

	GameStateClass = ABladeGameStateBase::StaticClass();

	static ConstructorHelpers::FClassFinder<UBladeGameFinishWidget> GameFinishHUD(TEXT("/Game/Blueprints/UMG/WB_GameFinish"));
	GameFinishWidgetClass = GameFinishHUD.Class;
}

void ABladeGameModeBase::BeginPlay()
{
	Super::BeginPlay();
	ClearPause();
}

void ABladeGameModeBase::GameOver()
{
	UGameplayStatics::SetGlobalTimeDilation(GetWorld(), 0.25f);

	FTimerDelegate TimerCallback;
	TimerCallback.BindLambda([this]()
	{
		UGameplayStatics::SetGlobalTimeDilation(GetWorld(), 1.0f);
		UGameplayStatics::SetGamePaused(GetWorld(), true);

		ABladePlayerControllerBase* Controller = Cast<ABladePlayerControllerBase>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
		if (Controller)
		{
			UWidgetBlueprintLibrary::SetInputMode_UIOnly(Controller);
			Controller->bShowMouseCursor = true;
		}

		if (GameFinishWidgetClass)
		{
			CreateWidget(GetWorld(), GameFinishWidgetClass)->AddToViewport();
		}
	});

	GetWorldTimerManager().SetTimer(TimerHandle, TimerCallback, 1.5f, false);
}
