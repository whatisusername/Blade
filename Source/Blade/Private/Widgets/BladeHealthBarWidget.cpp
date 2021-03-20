#include "BladeHealthBarWidget.h"

void UBladeHealthBarWidget::NativeConstruct()
{
	Super::NativeConstruct();
	SetVisibility(ESlateVisibility::Hidden);
}

void UBladeHealthBarWidget::UpdateHealth(float CurrentHealth, float MaxHealth)
{
	Super::UpdateHealth(CurrentHealth, MaxHealth);

	float Percentage = CurrentHealth / MaxHealth;
	if (Percentage > 0.0f)
	{
		SetVisibility(ESlateVisibility::Visible);
	}
	else
	{
		SetVisibility(ESlateVisibility::Hidden);
	}
}
