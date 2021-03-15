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

protected:
	virtual void BeginPlay() override;

public:
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
};
