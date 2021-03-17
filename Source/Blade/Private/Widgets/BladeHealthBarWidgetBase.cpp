#include "BladeHealthBarWidgetBase.h"
#include "Components/ProgressBar.h"

void UBladeHealthBarWidgetBase::UpdateHealthPercentage(float Percentage)
{
	if (HealthBar)
	{
		HealthBar->SetPercent(Percentage);
	}
}
