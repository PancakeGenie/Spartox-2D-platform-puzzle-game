// Puzzle platformer game done by Vladimir Mokanj - 15.02.2021

#include "Spartox_GameInstance.h"
#include "../SaveGame/Spartox_SaveGame.h"
#include "Kismet/GameplayStatics.h"

void USpartox_GameInstance::SaveGame(FString CurrentLevelName)
{
	FString TempSaveSlotName = "New Game " + FString::FromInt(GameIndex);		// Fixed value for now, will change later.

	// Cast to SaveGame and save current level name
	SaveGameInstance = Cast<USpartox_SaveGame>(UGameplayStatics::CreateSaveGameObject(USpartox_SaveGame::StaticClass()));
	SaveGameInstance->CurrentLevel = FName(*CurrentLevelName);

	// Save to slot
	UGameplayStatics::SaveGameToSlot(SaveGameInstance, TempSaveSlotName, GameIndex);
}

void USpartox_GameInstance::LoadGame(FString SaveSlotName)
{
	SaveGameInstance = Cast<USpartox_SaveGame>(UGameplayStatics::LoadGameFromSlot(SaveSlotName, 0));

	// Check if SaveSlot is empty
	if (!SaveGameInstance)
	{
		// Do something
		return;
	}

	// Load level if it exists
	UGameplayStatics::OpenLevel(GetWorld(), SaveGameInstance->CurrentLevel);
}