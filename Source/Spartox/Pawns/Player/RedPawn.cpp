// Puzzle platformer game done by Vladimir Mokanj - 15.02.2021

#include "RedPawn.h"
#include "../../Global_Log.h"
#include "Components/BoxComponent.h"

DEFINE_LOG_CATEGORY_STATIC(RedPawnLog, All, All)

ARedPawn::ARedPawn()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

void ARedPawn::Tick(float DeltaTime)
{
	RedRuntimeConfig();
}

void ARedPawn::RedRuntimeConfig()
{
	// If player is active, do this block
	if (isRedFirstTime == false && isRedPawn == true)
	{
		MeshCollision_COL->SetSimulatePhysics(true);

		isRedFirstTime = true;
	}

	// If player is inactive, do this block
	if (isRedFirstTime == true && isRedPawn == false)
	{
		MeshCollision_COL->SetSimulatePhysics(false);

		isRedFirstTime = false;
	}
}