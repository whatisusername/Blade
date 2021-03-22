#pragma once

#include "CoreMinimal.h"
#include "BladeWidgetBase.h"
#include "BladeHealthBarWidget.generated.h"

UCLASS()
class BLADE_API UBladeHealthBarWidget : public UBladeWidgetBase
{
	GENERATED_BODY()

public:
	virtual void UpdateHealth(float CurrentHealth, float MaxHealth) override;

protected:
	virtual void NativeConstruct() override;
};
