#include "BladeEnemyCharacter.h"
#include "BladeHealthBarWidgetBase.h"
#include "Components/WidgetComponent.h"

ABladeEnemyCharacter::ABladeEnemyCharacter()
{
	WidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("HPWidget"));
}

void ABladeEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();

	WidgetComponent->SetRelativeLocation(FVector(0, 0, 180));
	WidgetComponent->SetWidgetSpace(EWidgetSpace::Screen);
	WidgetComponent->SetDrawSize(FVector2D(100, 16));
	WidgetComponent->SetWidgetClass(WidgetClass.Get());
}
