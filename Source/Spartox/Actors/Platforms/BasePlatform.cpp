// Puzzle platformer game done by Vladimir Mokanj - 15.02.2021

#include "BasePlatform.h"
#include "Components/BoxComponent.h"

// Sets default values
ABasePlatform::ABasePlatform()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	// Create objects and link them
	PlatformCollision_COL = CreateDefaultSubobject<UBoxComponent>(TEXT("Platform Collision"));
	RootComponent = PlatformCollision_COL;

	PlatformMesh_SM = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Box Mesh"));
	PlatformMesh_SM->AttachToComponent(RootComponent, FAttachmentTransformRules::SnapToTargetIncludingScale);
}


