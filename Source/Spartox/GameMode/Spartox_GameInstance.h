// Puzzle platformer game done by Vladimir Mokanj - 15.02.2021

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Spartox_GameInstance.generated.h"

UCLASS()
class SPARTOX_API USpartox_GameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
	// Variables
	UPROPERTY(Category = "Save Game", BlueprintReadOnly, VisibleAnywhere)
		class USpartox_SaveGame* SaveGameInstance;
	UPROPERTY(Category = "Save Game", BlueprintReadWrite, EditAnywhere)
		FString SaveName;
	UPROPERTY(Category = "Save Game", BlueprintReadWrite, EditAnywhere)
		int32 GameIndex;

	// Functions
	UFUNCTION(BlueprintCallable)
		void SaveGame(FString CurrentLevelName);
	UFUNCTION(BlueprintCallable)
		void LoadGame(FString SaveSlotName);
};
