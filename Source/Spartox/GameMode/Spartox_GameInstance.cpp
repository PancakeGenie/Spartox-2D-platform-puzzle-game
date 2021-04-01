// Puzzle platformer game done by Vladimir Mokanj - 15.02.2021

#include "Spartox_GameInstance.h"
#include "../SaveGame/Spartox_SaveGame.h"
#include "Kismet/GameplayStatics.h"
#include "Misc/Paths.h"
#include "Kismet/KismetStringLibrary.h"
#include "../Global_Log.h"

DEFINE_LOG_CATEGORY_STATIC(GameInstanceLog, All, All)

USpartox_GameInstance::USpartox_GameInstance()
{
	SaveGamesList = GetAllSaveGameSlotNames();
}

// Function will save the current level to the game to slot (.sav). Game slot is based on player defined slot name, and assigned slot index.
void USpartox_GameInstance::SaveGame(UPARAM(ref) const FString &SaveSlotName, UPARAM(ref) const int32 &Index, FString CurrentLevelName)
{
	SaveGameInstance = Cast<USpartox_SaveGame>(UGameplayStatics::CreateSaveGameObject(USpartox_SaveGame::StaticClass()));

	// What to save
	SaveGameInstance->CurrentLevel = FName(*CurrentLevelName);

	// Where to save it
	UGameplayStatics::SaveGameToSlot(SaveGameInstance, SaveSlotName, Index);
}

// Function will open a specific level based on save slot name and it's index
void USpartox_GameInstance::LoadGame(UPARAM(ref) const FString& SaveSlotName, UPARAM(ref) const int32& Index)
{
	SaveGameInstance = Cast<USpartox_SaveGame>(UGameplayStatics::LoadGameFromSlot(SaveSlotName, Index));
	
	// Load level if it exists
	UGameplayStatics::OpenLevel(GetWorld(), SaveGameInstance->CurrentLevel);
}

void USpartox_GameInstance::DeleteGame(UPARAM(ref) const FString& SaveSlotName, UPARAM(ref) const int32& Index, UPARAM(ref) TArray<FString>& getSaveGamesList)
{
	// Delete Save slot in Saved/SaveGames dir
	UGameplayStatics::DeleteGameInSlot(SaveSlotName, Index);

	// Add "New Game" at deleted index
	getSaveGamesList[Index] = "New Game";
}

// Check if save game exists (whole array)
bool USpartox_GameInstance::DoesSaveExist(UPARAM(ref) const TArray<FString> &getSaveGamesList)
{
	for (uint8 i = 0; i < getSaveGamesList.Num(); ++i)
		if (getSaveGamesList[i] != "New Game")
			return true;
	

	return false;
}

// Find .sav extention inside SaveGames folder and write them onto SavesPath array
TArray<FString> USpartox_GameInstance::GetAllSaveGameSlotNames()
{
	// Temp Save list - exists troughout all game
	static TArray<FString> SaveGames;

	// Only do once
	if (SaveGames.Num() <= 0)
	{
		const FString SavePath = FPaths::ProjectSavedDir() + "SaveGames/";
		const FString SaveExtention = "*.sav";

		// Find files with .sav extention
		IFileManager::Get().FindFilesRecursive(SaveGames, *SavePath, *SaveExtention, true, false, false);

		// Remove extention
		for (uint8 i = 0; i < SaveGames.Num(); ++i)
			SaveGames[i] = FPaths::GetBaseFilename(SaveGames[i]);

		// Get file string names
		for (uint8 i = 0; i < 3; ++i)
		{
			// Sorting not necessary if array is smaller then loop value
			if (SaveGames.Num() > i)
			{
				// Sort current list
				for (uint8 y = i + 1; y < SaveGames.Num(); ++y)
				{
					// Sorting not necessary if current 'y' element is empty
					if (SaveGames[y].IsEmpty() == false)
					{
						const uint8 iVal = FCString::Atoi(*SaveGames[i].RightChop(SaveGames[i].Len() - 1));
						const uint8 yVal = FCString::Atoi(*SaveGames[y].RightChop(SaveGames[y].Len() - 1));

						// Switch element positions
						if (iVal > yVal)
						{
							const FString temp = SaveGames[i];
							SaveGames[i] = SaveGames[y];
							SaveGames[y] = temp;
						}
					}
				}
			}

			const FString &IndexExtention = "_" + FString::FromInt(i);

			// See if element with specific index exists, if it doesn't insert empty element
			if (SaveGames.Num() <= i || UKismetStringLibrary::FindSubstring(*SaveGames[i], *IndexExtention, false, false, 0) <= 0)
				SaveGames.Insert("New Game", i);
		}
	}

	return SaveGames;
}