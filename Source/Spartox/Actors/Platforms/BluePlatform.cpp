// Puzzle platformer game done by Vladimir Mokanj - 15.02.2021

#include "BluePlatform.h"
#include "../../Pawns/Player/BluePawn.h"

void ABluePlatform::BeginPlay()
{
	SpawnBluePlayer();
}

void ABluePlatform::SpawnBluePlayer()
{
	FVector SpawnLocation{GetActorLocation().X, 0.f, GetActorLocation().Z + SpawnDistance};
	FRotator SpawnRotation{ 0.f, 0.f, 0.f };
	FActorSpawnParameters SpawnInfo;

	GetWorld()->SpawnActor<ABluePawn>(SpawnLocation, SpawnRotation, SpawnInfo);
}