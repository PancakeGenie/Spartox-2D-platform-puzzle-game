// Puzzle platformer game done by Vladimir Mokanj - 15.02.2021

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "Spartox_SaveGame.generated.h"

UCLASS()
class SPARTOX_API USpartox_SaveGame : public USaveGame
{
	GENERATED_BODY()
	
public:
	// Variables
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
		FName CurrentLevel;
};
