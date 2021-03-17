#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "BladeHealthBarWidgetBase.generated.h"

class UProgressBar;

UCLASS()
class BLADE_API UBladeHealthBarWidgetBase : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(meta = (BindWidget))
	UProgressBar* HealthBar;

	UFUNCTION()
	void UpdateHealthPercentage(float Percentage);
};
