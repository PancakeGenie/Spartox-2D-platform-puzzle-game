// Puzzle platformer game done by Vladimir Mokanj - 15.02.2021

#include "Spartox_GameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "../SaveGame/Spartox_SaveGame.h"

ASpartox_GameModeBase::ASpartox_GameModeBase()
{
	DefaultPawnClass = nullptr;
	SaveGameInstance = Cast<USpartox_SaveGame>(UGameplayStatics::CreateSaveGameObject(USpartox_SaveGame::StaticClass()));
}

void ASpartox_GameModeBase::SaveGame(FString CurrentLevelName)
{
	SaveGameInstance = Cast<USpartox_SaveGame>(UGameplayStatics::CreateSaveGameObject(USpartox_SaveGame::StaticClass()));

	SaveGameInstance->CurrentLevel = FName(*CurrentLevelName);

	UGameplayStatics::SaveGameToSlot(SaveGameInstance, TEXT("First Slot"), 0);

	UE_LOG(LogTemp, Warning, TEXT("%s"), *CurrentLevelName);
}

void ASpartox_GameModeBase::LoadGame()
{
	SaveGameInstance = Cast<USpartox_SaveGame>(UGameplayStatics::LoadGameFromSlot("First Slot", 0));

	UGameplayStatics::OpenLevel(GetWorld(), SaveGameInstance->CurrentLevel);
}