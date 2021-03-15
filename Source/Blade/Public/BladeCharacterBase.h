#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BladeCharacterBase.generated.h"

UCLASS()
class BLADE_API ABladeCharacterBase : public ACharacter
{
	GENERATED_BODY()

public:
	ABladeCharacterBase() = default;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	void MoveForward(float AxisValue);
	void MoveRight(float AxisValue);
};
