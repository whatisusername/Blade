#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "BladeGameInstance.generated.h"

class UBladeSaveGame;
class USaveGame;

UCLASS()
class BLADE_API UBladeGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	UBladeGameInstance();

	virtual void Init() override;

	UFUNCTION(BlueprintCallable, Category = "Save")
	void LoadGameLevel();

	UFUNCTION(BlueprintCallable, Category = "Save")
	void RestartGameLevel();

	UFUNCTION(BlueprintCallable, Category = "Save")
	void SetSavingEnabled(bool bEnabled);

protected:
	UPROPERTY(BlueprintReadOnly, Category = "Save")
	FString SaveSlot;

	UPROPERTY(BlueprintReadWrite, Category = "Save")
	int32 SaveUserIndex;

	UPROPERTY()
	UBladeSaveGame* CurrentSaveGame;

	UPROPERTY()
	bool bSaveEnabled;

	UPROPERTY()
	bool bIsCurrentlySaving;

	UPROPERTY()
	bool bPendingSaveRequested;

	UFUNCTION(BlueprintCallable, Category = "Save")
	bool IsSaveGameExist();

	UFUNCTION(BlueprintCallable, Category = "Save")
	bool LoadSaveGame();

	UFUNCTION(BlueprintCallable, Category = "Save")
	bool CreateSaveGame();

	UFUNCTION(BlueprintCallable, Category = "Save")
	bool LoadOrCreateSaveGame();

	UFUNCTION(BlueprintCallable, Category = "Save")
	bool HandleSaveGameLoaded(USaveGame* SaveGameObject);

	UFUNCTION(BlueprintCallable, Category = "Save")
	void GetSaveSlotInfo(FString& SlotName, int32& UserIndex) const;

	UFUNCTION(BlueprintCallable, Category = "Save")
	UBladeSaveGame* GetCurrentSaveGame() const;

	UFUNCTION(BlueprintCallable, Category = "Save")
	bool WriteSaveGame();

	UFUNCTION(BlueprintCallable, Category = "Save")
	void ResetSaveGame();

	virtual void HandleAsyncSave(const FString& SlotName, const int32 UserIndex, bool bSuccess);
};
