// Puzzle platformer game done by Vladimir Mokanj - 15.02.2021

#include "RedPlatform.h"
#include "../../Pawns/Player/RedPawn.h"

void ARedPlatform::BeginPlay()
{
	SpawnRedPlayer();
}

void ARedPlatform::SpawnRedPlayer()
{
	FVector SpawnLocation{ GetActorLocation().X, 0.f, GetActorLocation().Z + SpawnDistance };
	FRotator SpawnRotation{ 0.f, 0.f, 0.f };
	FActorSpawnParameters SpawnInfo;

	GetWorld()->SpawnActor<ARedPawn>(SpawnLocation, SpawnRotation, SpawnInfo);
}