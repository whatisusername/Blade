#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "BladePlayerControllerBase.generated.h"

class UBladeWidgetBase;

UCLASS()
class BLADE_API ABladePlayerControllerBase : public APlayerController
{
	GENERATED_BODY()

public:
	void UpdateHealth(float CurrentHealth, float MaxHealth);

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Widget")
	TSubclassOf<UBladeWidgetBase> WidgetClass;

	UBladeWidgetBase* OwningWidget = nullptr;

	virtual void OnPossess(APawn* aPawn) override;
	virtual void OnUnPossess() override;
};
