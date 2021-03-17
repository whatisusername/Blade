#pragma once

#include "CoreMinimal.h"
#include "GameplayEffectExecutionCalculation.h"
#include "BladeAttributeSet.h"
#include "BladeDamageExecutionCalculation.generated.h"

UCLASS()
class BLADE_API UBladeDamageExecutionCalculation : public UGameplayEffectExecutionCalculation
{
	GENERATED_BODY()

public:
	UBladeDamageExecutionCalculation();

	virtual void Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams, FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const override;

protected:
	struct BladeDamageStatics
	{
		DECLARE_ATTRIBUTE_CAPTUREDEF(Damage);

		BladeDamageStatics()
		{
			DEFINE_ATTRIBUTE_CAPTUREDEF(UBladeAttributeSet, Damage, Source, true);
		}
	} DamageStatic;
	const BladeDamageStatics& GetDamageStatic() const;
};
