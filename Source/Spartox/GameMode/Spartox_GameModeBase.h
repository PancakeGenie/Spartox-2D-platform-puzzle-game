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
	// Variables
	bool isRedPawn;

	// Functions
	void SwitchPlayer();

protected:
	// Functions
	virtual void BeginPlay();

private:
	// Variables
	class ARedPawn* RedPawn;
	class ABluePawn* BluePawn;
	APlayerController* PlayerControllerRef;

	// Functions
	void HandlePlayerStart();
	void InitialPossession();
};
