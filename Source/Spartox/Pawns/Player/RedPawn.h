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
	// Constructor
	ARedPawn();

	// Functions
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInput) override;

private:
	// Variables
	float fSA_Distance;
	class ABluePawn* BluePawn;

	// Functions
	float PawnDistance(AActor* BluePawn);
	void SA_Check();
	void SA_Use();
};
