// Puzzle platformer game done by Vladimir Mokanj - 15.02.2021

#include "RedPlatform.h"
#include "../../Pawns/Player/RedPawn.h"

ARedPlatform::ARedPlatform()
{
	// Cast blueprint (reflection)
	static ConstructorHelpers::FObjectFinder<UBlueprint> RedPawn_BP(TEXT("Blueprint'/Game/Blueprints/Pawns/Player/RedPawn_BP.RedPawn_BP'"));
	if (RedPawn_BP.Object != nullptr)
		RedPlayer = (UClass*)RedPawn_BP.Object->GeneratedClass;
}

void ARedPlatform::BeginPlay()
{
	SpawnRedPlayer();
}

void ARedPlatform::SpawnRedPlayer()
{
	FVector SpawnLocation{ GetActorLocation().X, 0.f, GetActorLocation().Z + SpawnDistance };
	FRotator SpawnRotation{ 0.f, 0.f, 0.f };
	FActorSpawnParameters SpawnInfo;

	SpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	GetWorld()->SpawnActor<ARedPawn>(RedPlayer, SpawnLocation, SpawnRotation, SpawnInfo);
}