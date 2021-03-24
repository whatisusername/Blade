#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "BladeSaveGame.generated.h"

UCLASS()
class BLADE_API UBladeSaveGame : public USaveGame
{
	GENERATED_BODY()

public:
	UBladeSaveGame();

	UPROPERTY(VisibleAnywhere, Category = "Save")
	FString SaveSlot;

	UPROPERTY(VisibleAnywhere, Category = "Save")
	int32 SaveUserIndex;

	UPROPERTY(VisibleAnywhere, Category = "Save")
	FString LevelName;
};
