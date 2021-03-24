#pragma once

#include "CoreMinimal.h"
#include "BladeCharacterBase.h"
#include "BladePlayerCharacter.generated.h"

class UAIPerceptionStimuliSourceComponent;

UCLASS()
class BLADE_API ABladePlayerCharacter : public ABladeCharacterBase
{
	GENERATED_BODY()

public:
	ABladePlayerCharacter();

	virtual void HandleHealthChanged(float DeltaValue, const FGameplayTagContainer& EventTags) override;
	virtual void Die() override;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AI Perception")
	UAIPerceptionStimuliSourceComponent* StimuliSourceComponent;
};
