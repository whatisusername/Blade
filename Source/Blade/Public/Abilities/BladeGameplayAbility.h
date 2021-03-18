#pragma once

#include "CoreMinimal.h"
#include "BladeAbilityTypes.h"
#include "Abilities/GameplayAbility.h"
#include "BladeGameplayAbility.generated.h"

UENUM(BlueprintType)
enum class EBladeAbilityInputId : uint8
{
	None,
	Confirm,
	Cancel,
	NormalAttack
};

UCLASS()
class BLADE_API UBladeGameplayAbility : public UGameplayAbility
{
	GENERATED_BODY()

public:
	UBladeGameplayAbility() = default;

	EBladeAbilityInputId GetAbilityInputId() const;

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Ability")
	EBladeAbilityInputId AbilityInputId = EBladeAbilityInputId::None;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "GameplayEffect")
	TMap<FGameplayTag, FBladeGameplayEffectContainer> EffectContainerMap;

	/** Applies a gameplay effect container, by creating and then applying the spec */
	UFUNCTION(BlueprintCallable, Category = "Ability", meta = (AutoCreateRefTerm = "EventData"))
	virtual TArray<FActiveGameplayEffectHandle> ApplyEffectContainer(FGameplayTag ContainerTag, const FGameplayEventData& EventData, int32 OverrideGameplayLevel = -1);

	/** Search for and make a gameplay effect container spec to be applied later, from the EffectContainerMap */
	UFUNCTION(BlueprintCallable, Category = Ability, meta = (AutoCreateRefTerm = "EventData"))
	virtual FGASGameplayEffectContainerSpec MakeEffectContainerSpec(FGameplayTag ContainerTag, const FGameplayEventData& EventData, int32 OverrideGameplayLevel = -1);

	/** Make gameplay effect container spec to be applied later, using the passed in container */
	UFUNCTION(BlueprintCallable, Category = Ability, meta = (AutoCreateRefTerm = "EventData"))
	virtual FGASGameplayEffectContainerSpec MakeEffectContainerSpecFromContainer(const FBladeGameplayEffectContainer& Container, const FGameplayEventData& EventData, int32 OverrideGameplayLevel = -1);

	/** Applies a gameplay effect container spec that was previously created */
	UFUNCTION(BlueprintCallable, Category = Ability)
	virtual TArray<FActiveGameplayEffectHandle> ApplyEffectContainerSpec(const FGASGameplayEffectContainerSpec& ContainerSpec);
};
