#include "BladeEnemyCharacter.h"
#include "BladeHealthBarWidgetBase.h"
#include "Components/WidgetComponent.h"

ABladeEnemyCharacter::ABladeEnemyCharacter(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	WidgetComponent = ObjectInitializer.CreateDefaultSubobject<UWidgetComponent>(this, TEXT("HPWidget"));
	WidgetComponent->SetupAttachment(RootComponent);
	WidgetComponent->SetWidgetSpace(EWidgetSpace::Screen);
	WidgetComponent->SetDrawSize(FVector2D(100, 16));
}

void ABladeEnemyCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	WidgetComponent->SetWidgetClass(WidgetClass.Get());
	WidgetComponent->SetRelativeLocation(FVector(0, 0, 180));
}

void ABladeEnemyCharacter::UpdateHealthProgress()
{
	UBladeHealthBarWidgetBase* WidgetBase = WidgetClass.GetDefaultObject();
	float HealthPercentage = GetHealth() / GetMaxHealth();
	WidgetBase->UpdateHealthPercentage(HealthPercentage);

	if (HealthPercentage > 0.0f)
	{
		WidgetBase->SetVisibility(ESlateVisibility::Visible);
	}
	else
	{
		WidgetBase->SetVisibility(ESlateVisibility::Hidden);
	}
}
