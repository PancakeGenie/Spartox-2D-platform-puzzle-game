// Puzzle platformer game done by Vladimir Mokanj - 15.02.2021

#include "BluePawn.h"
#include "../../Global_Log.h"
#include "Components/BoxComponent.h"

DEFINE_LOG_CATEGORY_STATIC(BluePawnLog, All, All)

ABluePawn::ABluePawn()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

void ABluePawn::Tick(float DeltaTime)
{
	BlueRuntimeConfig();
}

void ABluePawn::BlueRuntimeConfig()
{
	// If player is active, do this block
	if (isBlueFirstTime == false && isRedPawn == false)
	{
		MeshCollision_COL->SetSimulatePhysics(true);

		isBlueFirstTime = true;
	}

	// If player is inactive, do this block
	if (isBlueFirstTime == true && isRedPawn == true)
	{
		MeshCollision_COL->SetSimulatePhysics(false);

		isBlueFirstTime = false;
	}
}