#include "BladeGameplayAbility_MeleeBase.h"
#include "AbilityTask_PlayMontageWithEvent.h"

void UBladeGameplayAbility_MeleeBase::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	if (CommitAbility(Handle, ActorInfo, ActivationInfo))
	{
		UAbilityTask_PlayMontageWithEvent* MontageProxy = UAbilityTask_PlayMontageWithEvent::PlayMontageAndWaitForEvent(this, TEXT("MeleeAttack"), MontageToPlay, MontageTags);
		MontageProxy->OnCompleted.AddDynamic(this, &UBladeGameplayAbility_MeleeBase::FinishAbility);
		MontageProxy->OnBlendOut.AddDynamic(this, &UBladeGameplayAbility_MeleeBase::FinishAbility);
		MontageProxy->OnInterrupted.AddDynamic(this, &UBladeGameplayAbility_MeleeBase::FinishAbility);
		MontageProxy->OnCancelled.AddDynamic(this, &UBladeGameplayAbility_MeleeBase::CancelAbility);
		MontageProxy->EventReceived.AddDynamic(this, &UBladeGameplayAbility_MeleeBase::ApplyEffects);

		MontageProxy->Activate();
	}
}

void UBladeGameplayAbility_MeleeBase::FinishAbility(FGameplayTag EventTag, FGameplayEventData EventData)
{
	EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true, false);
}

void UBladeGameplayAbility_MeleeBase::CancelAbility(FGameplayTag EventTag, FGameplayEventData EventData)
{
	EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, false, true);
}

void UBladeGameplayAbility_MeleeBase::ApplyEffects(FGameplayTag EventTag, FGameplayEventData EventData)
{
	ApplyEffectContainer(EventTag, EventData);
}
