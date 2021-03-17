#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "BladeHealthBarWidgetBase.generated.h"

UCLASS()
class BLADE_API UBladeHealthBarWidgetBase : public UUserWidget
{
	GENERATED_BODY()

public:
	explicit UBladeHealthBarWidgetBase(const FObjectInitializer& MovieSceneBlends);

	UFUNCTION(BlueprintImplementableEvent)
	void SetProgress(float Percentage);
};
