#include "BladeTargetType.h"
#include "BladeCharacterBase.h"

void UBladeTargetType_UseEventData::GetTargets(ABladeCharacterBase* TargetingCharacter,
											   AActor* TargetingActor,
											   FGameplayEventData EventData,
											   TArray<FHitResult>& OutHitResults,
											   TArray<AActor*>& OutActors) const
{
	const FHitResult* HitResult = EventData.ContextHandle.GetHitResult();
	if (HitResult)
	{
		OutHitResults.Add(*HitResult);
	}
	else if (EventData.Target)
	{
		OutActors.Add(const_cast<AActor*>(EventData.Target));
	}
}

void UBladeTargetType_UseOwner::GetTargets(ABladeCharacterBase* TargetingCharacter,
										   AActor* TargetingActor,
										   FGameplayEventData EventData,
										   TArray<FHitResult>& OutHitResults,
										   TArray<AActor*>& OutActors) const
{
	OutActors.Add(TargetingCharacter);
}
