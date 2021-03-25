// Puzzle platformer game done by Vladimir Mokanj - 15.02.2021

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Spartox_GameModeBase.generated.h"

UCLASS()
class SPARTOX_API ASpartox_GameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	// Constructor
	ASpartox_GameModeBase();

protected:
	// Variables
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
		class USpartox_GameInstance* GameInstanceRef;

	// Functions
	virtual void BeginPlay() override;
};
