#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "BladeGameFinishWidget.generated.h"

class UButton;

UCLASS()
class BLADE_API UBladeGameFinishWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;

	UFUNCTION()
	virtual void PlayAgain();

	UPROPERTY(meta = (BindWidget))
	UButton* PlayAgainButton;
};
