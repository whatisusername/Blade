#include "BladeAbilitySystemComponent.h"
#include "BladeGameplayAbility.h"

void UBladeAbilitySystemComponent::GetActiveAbilitiesWithTags(const FGameplayTagContainer& GameplayTagContainer, TArray<UBladeGameplayAbility*>& ActiveAbilities)
{
	TArray<FGameplayAbilitySpec*> AbilitySpecs;
	GetActivatableGameplayAbilitySpecsByAllMatchingTags(GameplayTagContainer, AbilitySpecs);

	for (FGameplayAbilitySpec* Spec : AbilitySpecs)
	{
		TArray<UGameplayAbility*> Abilities = Spec->GetAbilityInstances();
		for (UGameplayAbility* Ability : Abilities)
		{
			UBladeGameplayAbility* ActiveAbility = Cast<UBladeGameplayAbility>(Ability);
			if (ActiveAbility)
			{
				ActiveAbilities.Add(ActiveAbility);
			}
		}
	}
}
