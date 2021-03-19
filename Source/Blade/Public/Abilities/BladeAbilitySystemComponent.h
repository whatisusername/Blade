#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "BladeAbilitySystemComponent.generated.h"

class UBladeGameplayAbility;

UCLASS()
class BLADE_API UBladeAbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()

public:
	void GetActiveAbilitiesWithTags(const FGameplayTagContainer& GameplayTagContainer, TArray<UBladeGameplayAbility*>& ActiveAbilities);
};
