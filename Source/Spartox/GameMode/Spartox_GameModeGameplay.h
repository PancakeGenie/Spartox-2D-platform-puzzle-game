// Puzzle platformer game done by Vladimir Mokanj - 15.02.2021

#pragma once

#include "CoreMinimal.h"
#include "Spartox_GameModeBase.h"
#include "Spartox_GameModeGameplay.generated.h"

UCLASS()
class SPARTOX_API ASpartox_GameModeGameplay : public ASpartox_GameModeBase
{
	GENERATED_BODY()
	
public:
	// Functions
	void SwitchPlayer(bool& isRedPawn);

	UFUNCTION(BlueprintCallable)
		void NextLevel();

	UFUNCTION(BlueprintCallable)
		void ResetCurrentLevel();

protected:
	// Variables/Handles
	class ARedPawn* RedPawn;
	class ABluePawn* BluePawn;
	APlayerController* PlayerControllerRef;

	// Functions
	virtual void BeginPlay();

private:
	// Variables
	TArray<FName> LevelList;
	int32 CurrentLevel{ 0 };

	// Functions
	void GameStartConfig();
	void InitialPossession();
	TArray<FName> GetAllLevelNames();
	const int32 GetCurrentLevel(const TArray<FName>& GameLevels);
};
