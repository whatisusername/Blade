#include "BladeGameplayAbility_MeleeBase.h"
#include "Abilities/Tasks/AbilityTask_PlayMontageAndWait.h"

void UBladeGameplayAbility_MeleeBase::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	if (CommitAbility(Handle, ActorInfo, ActivationInfo))
	{
		UAbilityTask_PlayMontageAndWait* MontageProxy = UAbilityTask_PlayMontageAndWait::CreatePlayMontageAndWaitProxy(this, TEXT("MeleeAttack"), MontageToPlay);
		MontageProxy->OnCompleted.AddDynamic(this, &UBladeGameplayAbility_MeleeBase::FinishAbility);
		MontageProxy->OnBlendOut.AddDynamic(this, &UBladeGameplayAbility_MeleeBase::FinishAbility);
		MontageProxy->OnInterrupted.AddDynamic(this, &UBladeGameplayAbility_MeleeBase::FinishAbility);
		MontageProxy->OnCancelled.AddDynamic(this, &UBladeGameplayAbility_MeleeBase::FinishAbility);

		MontageProxy->Activate();
	}
}

void UBladeGameplayAbility_MeleeBase::FinishAbility()
{
	EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true, false);
}
