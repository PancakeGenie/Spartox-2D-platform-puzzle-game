// Puzzle platformer game done by Vladimir Mokanj - 15.02.2021

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Spartox_GameInstance.generated.h"

#define MAXSAVES 3

UCLASS()
class SPARTOX_API USpartox_GameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
	// Variables
	UPROPERTY(Category = "Save Game", BlueprintReadOnly, VisibleAnywhere)
		class USpartox_SaveGame* SaveGameInstance;
	UPROPERTY(Category = "Save Game", BlueprintReadWrite, EditAnywhere)
		TArray<FString>SaveGamesList;
	UPROPERTY(Category = "Save Game", BlueprintReadWrite, EditAnywhere)
		int32 GameIndex;
	UPROPERTY(Category = "Save Game", BlueprintReadWrite, EditAnywhere)
		FString SaveGameName;

	// Constructor
	USpartox_GameInstance();

	// Functions
	UFUNCTION(BlueprintCallable)
		void SaveGame(UPARAM(ref) const FString& SaveSlotName, UPARAM(ref) const int32& Index, FString CurrentLevelName = "Level_00");
	UFUNCTION(BlueprintCallable)
		void LoadGame(UPARAM(ref) const FString &SaveSlotName, UPARAM(ref) const int32& Index);
	UFUNCTION(BlueprintCallable)
		void DeleteGame(UPARAM(ref) const FString& SaveSlotName, UPARAM(ref) const int32& Index, UPARAM(ref) TArray<FString>& getSaveGamesList);

	UFUNCTION(BlueprintCallable)
		bool DoesSaveExist(UPARAM(ref) const TArray<FString> &getSaveGamesList);

private:
	// Variables
	uint8 MaxSaveGames{ MAXSAVES };

	// Functions
	static TArray<FString> GetAllSaveGameSlotNames();

};
