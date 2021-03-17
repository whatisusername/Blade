#pragma once

#include "CoreMinimal.h"
#include "Abilities/BladeGameplayAbility.h"
#include "BladeGameplayAbility_MeleeBase.generated.h"

UCLASS()
class BLADE_API UBladeGameplayAbility_MeleeBase : public UBladeGameplayAbility
{
	GENERATED_BODY()

public:
	UBladeGameplayAbility_MeleeBase() = default;

protected:
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;

	UFUNCTION()
	virtual void FinishAbility();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Abilites")
	UAnimMontage* MontageToPlay;
};
