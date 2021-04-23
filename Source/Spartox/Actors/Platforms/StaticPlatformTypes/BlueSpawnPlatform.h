// Puzzle platformer game done by Vladimir Mokanj - 15.02.2021

#pragma once

#include "CoreMinimal.h"
#include "../BasePlatform.h"
#include "BlueSpawnPlatform.generated.h"

UCLASS()
class SPARTOX_API ABlueSpawnPlatform : public ABasePlatform
{
	GENERATED_BODY()

public:
	// Constructor
	ABlueSpawnPlatform();

protected:
	// Functions
	virtual void BeginPlay() override;

private:
	// Variables
	float SpawnDistance{ 150.f };
	TSubclassOf<class ABluePawn> BluePlayer;

	// Functions
	void SpawnBluePlayer();
};