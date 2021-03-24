#include "BladeGameInstance.h"
#include "BladeSaveGame.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include "Kismet/GameplayStatics.h"

UBladeGameInstance::UBladeGameInstance()
	: SaveSlot(TEXT("SaveGame"))
	, SaveUserIndex(0)
	, CurrentSaveGame(nullptr)
	, bSaveEnabled(false)
	, bIsCurrentlySaving(false)
	, bPendingSaveRequested(false)
{
}

void UBladeGameInstance::Init()
{
	Super::Init();

	SetSavingEnabled(true);
	LoadOrCreateSaveGame();
}

void UBladeGameInstance::LoadGameLevel()
{
	UWidgetLayoutLibrary::RemoveAllWidgets(GetWorld());
	UGameplayStatics::OpenLevel(GetWorld(), *CurrentSaveGame->LevelName);
}

void UBladeGameInstance::RestartGameLevel()
{
	LoadGameLevel();
}

void UBladeGameInstance::SetSavingEnabled(bool bEnabled)
{
	bSaveEnabled = bEnabled;
}

bool UBladeGameInstance::IsSaveGameExist()
{
	return UGameplayStatics::DoesSaveGameExist(SaveSlot, SaveUserIndex);
}

bool UBladeGameInstance::LoadSaveGame()
{
	CurrentSaveGame = Cast<UBladeSaveGame>(UGameplayStatics::LoadGameFromSlot(SaveSlot, SaveUserIndex));
	return HandleSaveGameLoaded(CurrentSaveGame);
}

bool UBladeGameInstance::CreateSaveGame()
{
	return HandleSaveGameLoaded(CurrentSaveGame);
}

bool UBladeGameInstance::LoadOrCreateSaveGame()
{
	if (IsSaveGameExist())
	{
		return LoadSaveGame();
	}

	if (CreateSaveGame())
	{
		return WriteSaveGame();
	}

	return false;
}

bool UBladeGameInstance::HandleSaveGameLoaded(USaveGame* SaveGameObject)
{
	if (!bSaveEnabled)
	{
		return false;
	}

	CurrentSaveGame = Cast<UBladeSaveGame>(SaveGameObject);
	if (CurrentSaveGame)
	{
		return true;
	}

	USaveGame* SaveGame = UGameplayStatics::CreateSaveGameObject(UBladeSaveGame::StaticClass());
	CurrentSaveGame = Cast<UBladeSaveGame>(SaveGame);
	if (CurrentSaveGame)
	{
		FString MapName = GetWorld()->GetMapName();
		MapName.RemoveFromStart(GetWorld()->StreamingLevelsPrefix);
		CurrentSaveGame->LevelName = MapName;
		CurrentSaveGame->SaveSlot = SaveSlot;
		CurrentSaveGame->SaveUserIndex = SaveUserIndex;

		return true;
	}

	return false;
}

void UBladeGameInstance::GetSaveSlotInfo(FString& SlotName, int32& UserIndex) const
{
	SlotName = SaveSlot;
	UserIndex = SaveUserIndex;
}

UBladeSaveGame* UBladeGameInstance::GetCurrentSaveGame() const
{
	return CurrentSaveGame;
}

bool UBladeGameInstance::WriteSaveGame()
{
	if (!bSaveEnabled)
	{
		return false;
	}

	if (bIsCurrentlySaving)
	{
		bPendingSaveRequested = true;
		return true;
	}

	bIsCurrentlySaving = true;

	UGameplayStatics::AsyncSaveGameToSlot(CurrentSaveGame,
										  SaveSlot,
										  SaveUserIndex,
										  FAsyncSaveGameToSlotDelegate::CreateUObject(this, &UBladeGameInstance::HandleAsyncSave));
	return true;
}

void UBladeGameInstance::ResetSaveGame()
{
	HandleSaveGameLoaded(nullptr);
}

void UBladeGameInstance::HandleAsyncSave(const FString& SlotName, const int32 UserIndex, bool bSuccess)
{
	ensure(bIsCurrentlySaving);
	bIsCurrentlySaving = false;

	if (bPendingSaveRequested)
	{
		bPendingSaveRequested = false;
		WriteSaveGame();
	}
}
