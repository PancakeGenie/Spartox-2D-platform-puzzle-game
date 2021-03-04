// Puzzle platformer game done by Vladimir Mokanj - 15.02.2021

#pragma once

#include "CoreMinimal.h"
#include "BasePlatform.h"
#include "RedPlatform.generated.h"

UCLASS()
class SPARTOX_API ARedPlatform : public ABasePlatform
{
	GENERATED_BODY()
	
protected:
	// Functions
	virtual void BeginPlay() override;

private:
	// Variables
	float SpawnDistance{ 300.f };

	// Functions
	void SpawnRedPlayer();
};
