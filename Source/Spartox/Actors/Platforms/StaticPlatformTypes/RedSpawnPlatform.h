// Puzzle platformer game done by Vladimir Mokanj - 15.02.2021

#pragma once

#include "CoreMinimal.h"
#include "../BasePlatform.h"
#include "RedSpawnPlatform.generated.h"

UCLASS()
class SPARTOX_API ARedSpawnPlatform : public ABasePlatform
{
	GENERATED_BODY()
	
private:
	// Constructor
	ARedSpawnPlatform();

protected:
	// Functions
	virtual void BeginPlay() override;

private:
	// Variables
	float SpawnDistance{ 150.f };
	TSubclassOf<class ARedPawn> RedPlayer;

	// Functions
	void SpawnRedPlayer();
};