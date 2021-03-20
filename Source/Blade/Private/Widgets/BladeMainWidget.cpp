#include "BladeMainWidget.h"
#include "Components/TextBlock.h"

#define LOCTEXT_NAMESPACE "MyNamespace"

void UBladeMainWidget::UpdateHealth(float CurrentHealth, float MaxHealth)
{
	Super::UpdateHealth(CurrentHealth, MaxHealth);

	if (HealthText == nullptr)
	{
		return;
	}

	FFormatOrderedArguments Args;
	Args.Add(FText::AsNumber(CurrentHealth));
	Args.Add(FText::AsNumber(MaxHealth));
	FText Text = FText::Format(LOCTEXT("HealthFormatText", "{0} / {1}"), Args);
	HealthText->SetText(Text);
}

#undef LOCTEXT_NAMESPACE
