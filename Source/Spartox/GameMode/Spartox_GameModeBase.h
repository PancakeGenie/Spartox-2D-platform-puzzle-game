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
	// Functions
	virtual void SwitchPlayer(bool& isRedPawn);

protected:
	// Variables/Handles
	class ARedPawn* RedPawn;
	class ABluePawn* BluePawn;
	APlayerController* PlayerControllerRef;

	// Functions
	virtual void BeginPlay();

private:
	// Functions
	void HandlePlayerStart();
	void InitialPossession();
};
