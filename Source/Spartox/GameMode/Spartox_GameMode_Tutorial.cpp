// Puzzle platformer game done by Vladimir Mokanj - 15.02.2021

#include "Spartox_GameMode_Tutorial.h"
#include "../Pawns/Player/RedPawn.h"
#include "../Pawns/Player/BluePawn.h"

void ASpartox_GameMode_Tutorial::BeginPlay()
{
	// Run GameModeBase begin play
	Super::BeginPlay();

	// Player can't move, jump or switch on start in tutorial level
	BluePawn->SetCanPlayerJump(false);
	BluePawn->SetCanPlayerSwitch(false);
	BluePawn->SetCanPlayerMove(false);
}

void ASpartox_GameMode_Tutorial::SwitchPlayer(bool& isRedPawn)
{
	// For tutorial, player can't switch until certain checkpoint is reached
	if (BluePawn->GetCanPlayerSwitch() == false)
		return;

	Super::SwitchPlayer(isRedPawn);
}
