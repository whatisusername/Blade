#pragma once

#include "GameplayEffectTypes.h"
#include "Abilities/GameplayAbilityTargetTypes.h"
#include "BladeAbilityTypes.generated.h"

class UGameplayEffect;
class UBladeTargetType;

USTRUCT(BlueprintType)
struct FBladeGameplayEffectContainer
{
	GENERATED_BODY()

public:
	FBladeGameplayEffectContainer() = default;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "GameplayEffectContainer")
	TSubclassOf<UBladeTargetType> TargetType;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "GameplayEffectContainer")
	TArray<TSubclassOf<UGameplayEffect>> TargetGameplayEffectClasses;
};

USTRUCT(BlueprintType)
struct FGASGameplayEffectContainerSpec
{
	GENERATED_BODY()

public:
	FGASGameplayEffectContainerSpec() = default;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "GameplayEffectContainer")
	FGameplayAbilityTargetDataHandle TargetData;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "GameplayEffectContainer")
	TArray<FGameplayEffectSpecHandle> TargetGameplayEffectSpecs;

	/** Returns true if this has any valid effect specs */
	bool HasValidEffects() const;

	/** Returns true if this has any valid targets */
	bool HasValidTargets() const;

	/** Adds new targets to target data */
	void AddTargets(const TArray<FHitResult>& HitResults, const TArray<AActor*>& TargetActors);
};
