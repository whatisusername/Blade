#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbilityTypes.h"
#include "BladeTargetType.generated.h"

class ABladeCharacterBase;

UCLASS(Abstract)
class BLADE_API UBladeTargetType : public UObject
{
	GENERATED_BODY()

public:
	virtual void GetTargets(ABladeCharacterBase* TargetingCharacter,
							AActor* TargetingActor,
							FGameplayEventData EventData,
							TArray<FHitResult>& OutHitResults,
							TArray<AActor*>& OutActors) const PURE_VIRTUAL(UBladeTargetType::GetTargets);
};

UCLASS()
class BLADE_API UBladeTargetType_UseEventData : public UBladeTargetType
{
	GENERATED_BODY()

public:
	virtual void GetTargets(ABladeCharacterBase* TargetingCharacter,
							AActor* TargetingActor,
							FGameplayEventData EventData,
							TArray<FHitResult>& OutHitResults,
							TArray<AActor*>& OutActors) const override;
};

UCLASS()
class BLADE_API UBladeTargetType_UseOwner : public UBladeTargetType
{
	GENERATED_BODY()

public:
	virtual void GetTargets(ABladeCharacterBase* TargetingCharacter,
							AActor* TargetingActor,
							FGameplayEventData EventData,
							TArray<FHitResult>& OutHitResults,
							TArray<AActor*>& OutActors) const override;
};
