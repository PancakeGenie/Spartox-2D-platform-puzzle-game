// Puzzle platformer game done by Vladimir Mokanj - 15.02.2021

#include "Spartox_GameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "../Pawns/Player/BluePawn.h"
#include "../Pawns/Player/RedPawn.h"

void ASpartox_GameModeBase::BeginPlay()
{
	HandlePlayerStart();
}

void ASpartox_GameModeBase::HandlePlayerStart()
{
	// Assign values (pointers)
	RedPawn = Cast<ARedPawn>(UGameplayStatics::GetActorOfClass(GetWorld(), ARedPawn::StaticClass()));
	BluePawn = Cast<ABluePawn>(UGameplayStatics::GetActorOfClass(GetWorld(), ABluePawn::StaticClass()));
	PlayerControllerRef = Cast<APlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));

	// Initial player possession (Blue player)
	InitialPossession();
}

void ASpartox_GameModeBase::InitialPossession()
{
	// Check if player exists
	if (RedPawn == nullptr || BluePawn == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("RedPawn or BluePawn is empty!"));
		return;
	}

	PlayerControllerRef->Possess(BluePawn);
}

void ASpartox_GameModeBase::SwitchPlayer(bool& isRedPawn)
{
	// Check if player exists
	if (RedPawn == nullptr || BluePawn == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("RedPawn or BluePawn is empty!"));
		return;
	}

	// Depending on static isRedPawn variable, possession is either going to be Red player or Blue player
	isRedPawn == false ? PlayerControllerRef->Possess(RedPawn) : PlayerControllerRef->Possess(BluePawn);
	isRedPawn = !isRedPawn;
}