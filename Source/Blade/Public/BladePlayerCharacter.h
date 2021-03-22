#pragma once

#include "CoreMinimal.h"
#include "BladeCharacterBase.h"
#include "BladePlayerCharacter.generated.h"

UCLASS()
class BLADE_API ABladePlayerCharacter : public ABladeCharacterBase
{
	GENERATED_BODY()

public:
	virtual void HandleHealthChanged(float DeltaValue, const FGameplayTagContainer& EventTags) override;
	virtual void Die() override;
};
