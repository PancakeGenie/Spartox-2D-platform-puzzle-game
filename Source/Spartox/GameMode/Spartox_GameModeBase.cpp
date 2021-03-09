// Puzzle platformer game done by Vladimir Mokanj - 15.02.2021

#include "Spartox_GameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Engine/ObjectLibrary.h"
#include "../Global_Log.h"
#include "../Pawns/Player/BluePawn.h"
#include "../Pawns/Player/RedPawn.h"

DEFINE_LOG_CATEGORY_STATIC(GameModeLog, All, All)

void ASpartox_GameModeBase::BeginPlay()
{
	GameStartConfig();
}

// Game starting state
void ASpartox_GameModeBase::GameStartConfig()
{
	// Assign values (pointers)
	RedPawn = Cast<ARedPawn>(UGameplayStatics::GetActorOfClass(GetWorld(), ARedPawn::StaticClass()));
	BluePawn = Cast<ABluePawn>(UGameplayStatics::GetActorOfClass(GetWorld(), ABluePawn::StaticClass()));
	PlayerControllerRef = Cast<APlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));

	BluePawn->SetDefaltPlayer();				// Resets the static value (isRedPawn)
	LevelList = GetAllLevelNames();				
	CurrentLevel = GetCurrentLevel(LevelList);

	// Possess, take ownership, of Blue player
	InitialPossession();
}

void ASpartox_GameModeBase::InitialPossession()
{
	// Check if player exists
	if (RedPawn == nullptr || BluePawn == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("RedPawn or BluePawn is empty!"));
		return;
	}

	// Take control over Blue player
	PlayerControllerRef->Possess(BluePawn);
}

void ASpartox_GameModeBase::SwitchPlayer(bool& isRedPawn)
{
	// Check if player exists
	if (RedPawn == nullptr || BluePawn == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("RedPawn or BluePawn is empty!"));
		return;
	}

	// Depending on static isRedPawn variable, possession is either going to be Red player or Blue player
	isRedPawn == false ? PlayerControllerRef->Possess(RedPawn) : PlayerControllerRef->Possess(BluePawn);
	isRedPawn = !isRedPawn;
}

// Return the list of levels that exist in game
TArray<FName> ASpartox_GameModeBase::GetAllLevelNames()
{
	UObjectLibrary* ObjectLibrary = UObjectLibrary::CreateLibrary(UWorld::StaticClass(), false, true);
	TArray<FAssetData> MapData;
	TArray<FName> LevelNames;

	// Load and write the maps
	ObjectLibrary->LoadAssetDataFromPath(TEXT("/Game/Levels"));
	ObjectLibrary->GetAssetDataList(MapData);

	// Write all the levels in an array
	for (int32 i = 0; i < MapData.Num(); ++i)
	{
		const FString CurrentLevelSName = "/Game/Levels/" + MapData[i].AssetName.ToString();
		const FName CurrentLevelName = FName(*CurrentLevelSName);

		LevelNames.Add(CurrentLevelName);
	}

	return LevelNames;
}

// Return current level from list of levels that exist in the game
const int32 ASpartox_GameModeBase::GetCurrentLevel(const TArray<FName>& GameLevels)
{
	int32 LevelIndex;
	FString CurrentLevelName = GetWorld()->GetMapName();

	CurrentLevelName.RemoveFromStart(GetWorld()->StreamingLevelsPrefix);	// Remove prefix from map name
	CurrentLevelName = "/Game/Levels/" + CurrentLevelName;

	// Find the current level
	for (int32 i = 0; i < GameLevels.Num(); i++)
	{
		if (CurrentLevelName == GameLevels[i].ToString())
		{
			LevelIndex = i;
			break;
		}
	}

	return LevelIndex;
}

// Switch to next level, if there is one
void ASpartox_GameModeBase::NextLevel()
{
	if (CurrentLevel < LevelList.Num() - 1)
	{
		UGameplayStatics::OpenLevel(GetWorld(), LevelList[CurrentLevel], TRAVEL_Absolute);
	}
	else
	{
		UKismetSystemLibrary::QuitGame(this, UGameplayStatics::GetPlayerController(this, 0), EQuitPreference::Quit, true);
	}
}

// Resets the current, triggered by overlapping the triggerbox (on level) or manually by player
void ASpartox_GameModeBase::ResetCurrentLevel()
{
	UGameplayStatics::OpenLevel(GetWorld(), LevelList[CurrentLevel], TRAVEL_Absolute);
}