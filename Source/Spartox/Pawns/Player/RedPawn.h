// Puzzle platformer game done by Vladimir Mokanj - 15.02.2021

#pragma once

#include "CoreMinimal.h"
#include "BasePawn.h"
#include "RedPawn.generated.h"

UCLASS()
class SPARTOX_API ARedPawn : public ABasePawn
{
	GENERATED_BODY()

public:
	// Variables
	bool isRedFirstTime{ false };

	// Constructor
	ARedPawn();

	// Functions
	virtual void Tick(float DeltaTime) override;

private:
	// Functions
	void RedRuntimeConfig();
};
