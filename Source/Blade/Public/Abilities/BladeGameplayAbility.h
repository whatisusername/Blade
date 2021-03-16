#pragma once

#include "CoreMinimal.h"
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

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Ability")
	EBladeAbilityInputId AbilityInputId = EBladeAbilityInputId::None;
};
