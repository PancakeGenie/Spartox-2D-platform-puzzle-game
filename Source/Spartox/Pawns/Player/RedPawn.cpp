// Puzzle platformer game done by Vladimir Mokanj - 15.02.2021

#include "RedPawn.h"
#include "PawnSkills.h"

ARedPawn::ARedPawn()
{
	fSA_Distance = 400.f;
}

void ARedPawn::SetupPlayerInputComponent(UInputComponent* PlayerInput)
{
	Super::SetupPlayerInputComponent(PlayerInput);

	// Link special ability
	PlayerInput->BindAction("SpecialAbility", EInputEvent::IE_Pressed, this, &ARedPawn::SA_Check);
	PlayerInput->BindAction("SpecialAbility", EInputEvent::IE_Released, this, &ARedPawn::SA_Use);
}

void ARedPawn::SA_Check()
{
	/*if (PawnDistance(GameModeRef->) <= fSA_Distance)
	{
		// Highlight BluePawn
	}*/

	// Repeat SA_Check function until button is released *timer*
}

void ARedPawn::SA_Use()
{
	/*if (PawnDistance() <= fSA_Distance)
	{
		// Grab BluePawn
	}*/

	// Stop SA_Check function *timer* 
}

/*float ARedPawn::PawnDistance(AActor* BluePawn)
{
	return FVector::Dist(GetActorLocation(), BluePawn->GetActorLocation());
}*/