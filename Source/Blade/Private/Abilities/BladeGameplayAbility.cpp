#include "BladeGameplayAbility.h"
#include "BladeAbilitySystemComponent.h"
#include "BladeCharacterBase.h"
#include "BladeTargetType.h"

EBladeAbilityInputId UBladeGameplayAbility::GetAbilityInputId() const
{
	return AbilityInputId;
}

TArray<FActiveGameplayEffectHandle> UBladeGameplayAbility::ApplyEffectContainer(FGameplayTag ContainerTag, const FGameplayEventData& EventData, int32 OverrideGameplayLevel)
{
	FGASGameplayEffectContainerSpec ContainerSpec = MakeEffectContainerSpec(ContainerTag, EventData, OverrideGameplayLevel);
	return ApplyEffectContainerSpec(ContainerSpec);
}

FGASGameplayEffectContainerSpec UBladeGameplayAbility::MakeEffectContainerSpec(FGameplayTag ContainerTag, const FGameplayEventData& EventData, int32 OverrideGameplayLevel)
{
	FBladeGameplayEffectContainer* Container = EffectContainerMap.Find(ContainerTag);
	if (Container)
	{
		return MakeEffectContainerSpecFromContainer(*Container, EventData, OverrideGameplayLevel);
	}
	return FGASGameplayEffectContainerSpec();
}

FGASGameplayEffectContainerSpec UBladeGameplayAbility::MakeEffectContainerSpecFromContainer(const FBladeGameplayEffectContainer& Container,
																							const FGameplayEventData& EventData,
																							int32 OverrideGameplayLevel)
{
	FGASGameplayEffectContainerSpec ContainerSpec;
	AActor* OwningActor = GetOwningActorFromActorInfo();
	ABladeCharacterBase* OwningCharacter = Cast<ABladeCharacterBase>(OwningActor);

	if (Container.TargetType.Get())
	{
		TArray<FHitResult> HitResults;
		TArray<AActor*> TargetActors;
		UBladeTargetType* TargetType = Container.TargetType.GetDefaultObject();
		AActor* AvatarActor = GetAvatarActorFromActorInfo();
		TargetType->GetTargets(OwningCharacter, AvatarActor, EventData, HitResults, TargetActors);
		ContainerSpec.AddTargets(HitResults, TargetActors);
	}

	if (OverrideGameplayLevel == INDEX_NONE)
	{
		OverrideGameplayLevel = GetAbilityLevel();
	}

	for (const TSubclassOf<UGameplayEffect> EffectClass : Container.TargetGameplayEffectClasses)
	{
		ContainerSpec.TargetGameplayEffectSpecs.Add(MakeOutgoingGameplayEffectSpec(EffectClass, OverrideGameplayLevel));
	}

	return ContainerSpec;
}

TArray<FActiveGameplayEffectHandle> UBladeGameplayAbility::ApplyEffectContainerSpec(const FGASGameplayEffectContainerSpec& ContainerSpec)
{
	TArray<FActiveGameplayEffectHandle> Handles;
	for (const FGameplayEffectSpecHandle SpecHandle : ContainerSpec.TargetGameplayEffectSpecs)
	{
		Handles.Append(K2_ApplyGameplayEffectSpecToTarget(SpecHandle, ContainerSpec.TargetData));
	}
	return Handles;
}
