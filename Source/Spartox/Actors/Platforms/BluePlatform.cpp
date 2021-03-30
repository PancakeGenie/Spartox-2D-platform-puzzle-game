// Puzzle platformer game done by Vladimir Mokanj - 15.02.2021

#include "BluePlatform.h"
#include "../../Pawns/Player/BluePawn.h"

ABluePlatform::ABluePlatform()
{
	// Cast blueprint (reflection)
	static ConstructorHelpers::FObjectFinder<UClass> BluePawn_BP(TEXT("Class'/Game/Blueprints/Pawns/Player/BluePawn_BP.BluePawn_BP_C'"));
	if (BluePawn_BP.Object != nullptr)
		BluePlayer = BluePawn_BP.Object;
}

void ABluePlatform::BeginPlay()
{
	SpawnBluePlayer();
}

void ABluePlatform::SpawnBluePlayer()
{
	FVector SpawnLocation{GetActorLocation().X, 0.f, GetActorLocation().Z + SpawnDistance};
	FRotator SpawnRotation{ 0.f, 0.f, 0.f };
	FActorSpawnParameters SpawnInfo;

	SpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	GetWorld()->SpawnActor<ABluePawn>(BluePlayer, SpawnLocation, SpawnRotation, SpawnInfo);
}