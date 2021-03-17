#pragma once

#include "GameplayEffect.h"
#include "BladeAbilityTypes.generated.h"

USTRUCT(BlueprintType)
struct FBladeGameplayEffectContainer
{
	GENERATED_BODY()

public:
	FBladeGameplayEffectContainer() = default;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "GameplayEffectContainer")
	TArray<TSubclassOf<UGameplayEffect>> TargetGameplayEffectClasses;
};
