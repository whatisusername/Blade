#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "BladeWidgetBase.generated.h"

class UProgressBar;

UCLASS()
class BLADE_API UBladeWidgetBase : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void UpdateHealth(float CurrentHealth, float MaxHealth);

protected:
	UPROPERTY(meta = (BindWidget))
	UProgressBar* HealthBar = nullptr;
};
