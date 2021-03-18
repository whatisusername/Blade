#include "BladeHealthBarWidgetBase.h"
#include "Components/ProgressBar.h"

void UBladeHealthBarWidgetBase::NativeConstruct()
{
	Super::NativeConstruct();
	SetVisibility(ESlateVisibility::Hidden);
}

void UBladeHealthBarWidgetBase::UpdateHealthPercentage(float Percentage)
{
	if (HealthBar == nullptr)
	{
		return;
	}

	HealthBar->SetPercent(Percentage);
	if (Percentage > 0.0f)
	{
		SetVisibility(ESlateVisibility::Visible);
	}
	else
	{
		SetVisibility(ESlateVisibility::Hidden);
	}
}
