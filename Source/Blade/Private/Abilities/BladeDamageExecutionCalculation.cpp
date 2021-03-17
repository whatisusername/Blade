#include "BladeDamageExecutionCalculation.h"

UBladeDamageExecutionCalculation::UBladeDamageExecutionCalculation()
{
	RelevantAttributesToCapture.Add(GetDamageStatic().DamageDef);
}

void UBladeDamageExecutionCalculation::Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams, FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const
{
	const FGameplayEffectSpec& Spec = ExecutionParams.GetOwningSpec();

	const FGameplayTagContainer* SourceTags = Spec.CapturedSourceTags.GetAggregatedTags();
	const FGameplayTagContainer* TargetTags = Spec.CapturedTargetTags.GetAggregatedTags();

	FAggregatorEvaluateParameters EvaluationParameters;
	EvaluationParameters.SourceTags = SourceTags;
	EvaluationParameters.TargetTags = TargetTags;

	float Damage = 0.0f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(GetDamageStatic().DamageDef, EvaluationParameters, Damage);

	if (Damage > 0.f)
	{
		OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(GetDamageStatic().DamageProperty, EGameplayModOp::Additive, Damage));
	}
}

const UBladeDamageExecutionCalculation::BladeDamageStatics& UBladeDamageExecutionCalculation::GetDamageStatic() const
{
	static BladeDamageStatics DamageStatics;
	return DamageStatics;
}
