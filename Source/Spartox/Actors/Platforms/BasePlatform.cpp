// Puzzle platformer game done by Vladimir Mokanj - 15.02.2021

#include "BasePlatform.h"
#include "Components/BoxComponent.h"

// Sets default values
ABasePlatform::ABasePlatform()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	// Create all objects and link them
	// ---------------------------------
	// Responsible for collision detection
	Platform_COL = CreateDefaultSubobject<UBoxComponent>(TEXT("Collision Box"));
	RootComponent = Platform_COL;

	// Visible mesh to player
	Platform_SM = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Box Mesh"));
	Platform_SM->SetupAttachment(RootComponent);
}