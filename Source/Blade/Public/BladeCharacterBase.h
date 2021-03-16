#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GameplayTagContainer.h"
#include "BladeCharacterBase.generated.h"

class UBladeAttributeSet;

UCLASS()
class BLADE_API ABladeCharacterBase : public ACharacter
{
	GENERATED_BODY()

public:
	ABladeCharacterBase();

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void HandleDamage(float DamageAmount, const FHitResult& HitInfo, const struct FGameplayTagContainer& DamageTags, ABladeCharacterBase* InstigatorCharacter, AActor* DamageCauser);
	virtual void HandleHealthChanged(float DeltaValue, const struct FGameplayTagContainer& EventTags);

	UFUNCTION(BlueprintCallable)
	virtual float GetHealth() const;

	UFUNCTION(BlueprintCallable)
	virtual float GetMaxHealth() const;

protected:
	void MoveForward(float AxisValue);
	void MoveRight(float AxisValue);

	UFUNCTION(BlueprintImplementableEvent)
	void OnDamaged(float DamageAmount, const FHitResult& HitInfo, const struct FGameplayTagContainer& DamageTags, ABladeCharacterBase* InstigatorCharacter, AActor* DamageCauser);

	UFUNCTION(BlueprintImplementableEvent)
	void OnHealthChanged(float DeltaValue, const struct FGameplayTagContainer& EventTags);

	UPROPERTY()
	UBladeAttributeSet* AttributeSet;
};
