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
	void UpdateHealthPercentage(float Percentage);

protected:
	UPROPERTY(meta = (BindWidget))
	UProgressBar* HealthBar = nullptr;

	virtual void NativeConstruct() override;
};
