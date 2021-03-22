#include "BladeEnemyCharacter.h"
#include "BladeAIController.h"
#include "BladeHealthBarWidget.h"
#include "Components/WidgetComponent.h"

ABladeEnemyCharacter::ABladeEnemyCharacter(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	AIControllerClass = ABladeAIController::StaticClass();

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

void ABladeEnemyCharacter::HandleHealthChanged(float DeltaValue, const FGameplayTagContainer& EventTags)
{
	Super::HandleHealthChanged(DeltaValue, EventTags);
	UpdateHealthProgress();
}

void ABladeEnemyCharacter::UpdateHealthProgress()
{
	UBladeHealthBarWidget* Widget = Cast<UBladeHealthBarWidget>(WidgetComponent->GetUserWidgetObject());

	if (Widget)
	{
		float HealthPercentage = GetHealth() / GetMaxHealth();
		Widget->UpdateHealth(GetHealth(), GetMaxHealth());
	}
}
