#include "BladeEnemyCharacter.h"
#include "Components/WidgetComponent.h"

ABladeEnemyCharacter::ABladeEnemyCharacter()
{
	WidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("HPWidget"));
}
