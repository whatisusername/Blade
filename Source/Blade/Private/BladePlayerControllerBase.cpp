#include "BladePlayerControllerBase.h"
#include "BladeCharacterBase.h"
#include "BladeWidgetBase.h"
#include "Blueprint/UserWidget.h"

void ABladePlayerControllerBase::OnPossess(APawn* aPawn)
{
	Super::OnPossess(aPawn);

	ABladeCharacterBase* PlayerCharacter = Cast<ABladeCharacterBase>(aPawn);
	if (PlayerCharacter)
	{
		OwningWidget = CreateWidget<UBladeWidgetBase>(this, WidgetClass);
		OwningWidget->UpdateHealth(PlayerCharacter->GetHealth(), PlayerCharacter->GetMaxHealth());
		OwningWidget->AddToViewport();
	}
}

void ABladePlayerControllerBase::OnUnPossess()
{
	Super::OnUnPossess();

	if (OwningWidget)
	{
		OwningWidget->RemoveFromViewport();
	}
}
