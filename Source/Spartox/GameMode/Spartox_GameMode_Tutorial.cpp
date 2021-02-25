// Puzzle platformer game done by Vladimir Mokanj - 15.02.2021

#include "Spartox_GameMode_Tutorial.h"
#include "../Pawns/Player/RedPawn.h"
#include "../Pawns/Player/BluePawn.h"

void ASpartox_GameMode_Tutorial::BeginPlay()
{
	// Run GameModeBase begin play
	Super::BeginPlay();

	// Set specific default values for tutorial
	BluePawn->SetCanPawnJump(false);
	BluePawn->SetCanPawnSwitch(false);

	StartingWidget();
}

void ASpartox_GameMode_Tutorial::SwitchPlayer()
{
	// For tutorial, player can't switch until certain checkpoint is reached
	if (BluePawn->GetCanPawnSwitch() == false)
		return;

	Super::SwitchPlayer();
}
