#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "BladeGameModeBase.generated.h"

class UBladeGameFinishWidget;

UCLASS()
class BLADE_API ABladeGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	ABladeGameModeBase();

	UFUNCTION(BlueprintCallable, Category = "Game")
	virtual void GameOver();

protected:
	UPROPERTY()
	FTimerHandle TimerHandle;

	UPROPERTY()
	TSubclassOf<UBladeGameFinishWidget> GameFinishWidgetClass;

	virtual void BeginPlay() override;
};
