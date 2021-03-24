#include "BladeGameFinishWidget.h"
#include "BladeGameInstance.h"
#include "Components/Button.h"

void UBladeGameFinishWidget::NativeConstruct()
{
	Super::NativeConstruct();
	PlayAgainButton->OnClicked.AddDynamic(this, &UBladeGameFinishWidget::PlayAgain);
}

void UBladeGameFinishWidget::PlayAgain()
{
	RemoveFromParent();

	UBladeGameInstance* GameInstance = GetGameInstance<UBladeGameInstance>();
	if (GameInstance)
	{
		GameInstance->RestartGameLevel();
	}
}
