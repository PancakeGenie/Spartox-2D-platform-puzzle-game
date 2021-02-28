// Puzzle platformer game done by Vladimir Mokanj - 15.02.2021

#pragma once

#include "CoreMinimal.h"
#include "Spartox_GameModeBase.h"
#include "Spartox_GameMode_Tutorial.generated.h"

UCLASS()
class SPARTOX_API ASpartox_GameMode_Tutorial : public ASpartox_GameModeBase
{
	GENERATED_BODY()
	
public:
	virtual void SwitchPlayer(bool& isRedPawn) override;

protected:
	virtual void BeginPlay() override;

private:
	// Variables
	bool canSwitch{ false };
	bool canJump{ false };
};
