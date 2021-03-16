#pragma once

#include "CoreMinimal.h"
#include "BladeCharacterBase.h"
#include "BladeEnemyCharacter.generated.h"

class UWidgetComponent;

UCLASS()
class BLADE_API ABladeEnemyCharacter : public ABladeCharacterBase
{
	GENERATED_BODY()

public:
	ABladeEnemyCharacter();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UWidgetComponent* WidgetComponent;
};
