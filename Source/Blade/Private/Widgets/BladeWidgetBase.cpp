#include "BladeWidgetBase.h"
#include "Components/ProgressBar.h"

void UBladeWidgetBase::UpdateHealth(float CurrentHealth, float MaxHealth)
{
	if (HealthBar == nullptr)
	{
		return;
	}

	float Percentage = CurrentHealth / MaxHealth;
	HealthBar->SetPercent(Percentage);
}
