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
	// Assign handle values
	RedPawn = Cast<ARedPawn>(UGameplayStatics::GetActorOfClass(GetWorld(), ARedPawn::StaticClass()));
	BluePawn = Cast<ABluePawn>(UGameplayStatics::GetActorOfClass(GetWorld(), ABluePawn::StaticClass()));
	PlayerControllerRef = Cast<APlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));

	/*
	if (RedPawn != nullptr)
		UE_LOG(LogTemp, Warning, TEXT("RedPawn: %s"), *RedPawn->GetName());
	if (BluePawn != nullptr)
		UE_LOG(LogTemp, Warning, TEXT("BluePawn: %s"), *BluePawn->GetName());
	*/

	// Possess BluePawn (Blue player)
	InitialPossession();
}

void ASpartox_GameModeBase::InitialPossession()
{
	// Check if pawn exists
	if (RedPawn == nullptr || BluePawn == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("RedPawn or BluePawn is empty!"));
		return;
	}

	// Assign player to start as Blue pawn
	PlayerControllerRef->Possess(BluePawn);
}

void ASpartox_GameModeBase::SwitchPlayer(bool& isRedPawn)
{
	// Check if pawn exists
	if (RedPawn == nullptr || BluePawn == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("RedPawn or BluePawn is empty!"));
		return;
	}

	isRedPawn == false ? PlayerControllerRef->Possess(RedPawn) : PlayerControllerRef->Possess(BluePawn);
	isRedPawn = !isRedPawn;
}