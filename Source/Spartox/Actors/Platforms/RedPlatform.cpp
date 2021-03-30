// Puzzle platformer game done by Vladimir Mokanj - 15.02.2021

#include "RedPlatform.h"
#include "../../Pawns/Player/RedPawn.h"

ARedPlatform::ARedPlatform()
{
	// Cast blueprint (reflection)
	static ConstructorHelpers::FObjectFinder<UClass> RedPawn_BP(TEXT("Class'/Game/Blueprints/Pawns/Player/RedPawn_BP.RedPawn_BP_C'"));
	if (RedPawn_BP.Object != nullptr)
		RedPlayer = RedPawn_BP.Object;
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