// Puzzle platformer game done by Vladimir Mokanj - 15.02.2021

#pragma once

#include "CoreMinimal.h"
#include "BasePawn.h"
#include "BluePawn.generated.h"

UCLASS()
class SPARTOX_API ABluePawn : public ABasePawn
{
	GENERATED_BODY()

public:	
	// Variables
	bool isBlueFirstTime{ false };

	// Constructor
	ABluePawn();

	// Functions
	virtual void Tick(float DeltaTime);

private:
	// Functions
	void BlueRuntimeConfig();

};
