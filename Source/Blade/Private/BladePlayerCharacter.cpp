#include "BladePlayerCharacter.h"
#include "BladeGameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "Perception/AIPerceptionStimuliSourceComponent.h"

ABladePlayerCharacter::ABladePlayerCharacter()
{
	StimuliSourceComponent = CreateDefaultSubobject<UAIPerceptionStimuliSourceComponent>(TEXT("StimuliSourceComponent"));
}

void ABladePlayerCharacter::HandleHealthChanged(float DeltaValue, const FGameplayTagContainer& EventTags)
{
	Super::HandleHealthChanged(DeltaValue, EventTags);

	if (!IsAlive())
	{
		Die();
	}
}

void ABladePlayerCharacter::Die()
{
	Super::Die();

	ABladeGameModeBase* GameMode = Cast<ABladeGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
	if (GameMode)
	{
		GameMode->GameOver();
	}
}
