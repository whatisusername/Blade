#pragma once

#include "CoreMinimal.h"
#include "BladeWidgetBase.h"
#include "BladeMainWidget.generated.h"

class UTextBlock;

UCLASS()
class BLADE_API UBladeMainWidget : public UBladeWidgetBase
{
	GENERATED_BODY()

public:
	virtual void UpdateHealth(float CurrentHealth, float MaxHealth) override;

protected:
	UPROPERTY(meta = (BindWidget))
	UTextBlock* HealthText = nullptr;
};
