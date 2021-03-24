#include "BladePlayerControllerBase.h"
#include "BladeCharacterBase.h"
#include "BladeWidgetBase.h"
#include "Blueprint/UserWidget.h"
#include "Blueprint/WidgetBlueprintLibrary.h"

void ABladePlayerControllerBase::UpdateHealth(float CurrentHealth, float MaxHealth)
{
	OwningWidget->UpdateHealth(CurrentHealth, MaxHealth);
}

void ABladePlayerControllerBase::OnPossess(APawn* aPawn)
{
	Super::OnPossess(aPawn);

	ABladeCharacterBase* PlayerCharacter = Cast<ABladeCharacterBase>(aPawn);
	if (PlayerCharacter)
	{
		OwningWidget = CreateWidget<UBladeWidgetBase>(this, WidgetClass);
		OwningWidget->AddToViewport();
		UpdateHealth(PlayerCharacter->GetHealth(), PlayerCharacter->GetMaxHealth());
	}

	UWidgetBlueprintLibrary::SetInputMode_GameOnly(this);
}

void ABladePlayerControllerBase::OnUnPossess()
{
	Super::OnUnPossess();

	if (OwningWidget)
	{
		OwningWidget->RemoveFromViewport();
	}
}
