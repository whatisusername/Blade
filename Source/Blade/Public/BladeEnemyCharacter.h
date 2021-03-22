#pragma once

#include "CoreMinimal.h"
#include "BladeCharacterBase.h"
#include "BladeEnemyCharacter.generated.h"

class UBladeHealthBarWidget;
class UWidgetComponent;

UCLASS()
class BLADE_API ABladeEnemyCharacter : public ABladeCharacterBase
{
	GENERATED_BODY()

public:
	explicit ABladeEnemyCharacter(const FObjectInitializer& ObjectInitializer);
	virtual void PostInitializeComponents() override;

protected:
	UPROPERTY()
	UWidgetComponent* WidgetComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Widget")
	TSubclassOf<UBladeHealthBarWidget> WidgetClass;

	virtual void UpdateHealthProgress() override;
};
