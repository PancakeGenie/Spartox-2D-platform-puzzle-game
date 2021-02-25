// Puzzle platformer game done by Vladimir Mokanj - 15.02.2021

#include "Tutorial_BaseTriggerBox.h"
#include "Kismet/GameplayStatics.h"

void ATutorial_BaseTriggerBox::BeginPlay()
{
	// Dynamic (OnOverlap)
	OnActorBeginOverlap.AddDynamic(this, &ATutorial_BaseTriggerBox::OnOverlap);
}
// ------------------------------------------------------------------------------------------------------------------------------

// ------------------------------------------------------------------------------------------------------------------------------
// Trigger overlap function -----------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------------------------------------
void ATutorial_BaseTriggerBox::OnOverlap(AActor* OtherActor, AActor* PlayerActor)
{
	// Cast Pawn
	AActor* PawnActorRef = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);

	// Check trigger box was overlapped and if overlapping actor was player pawn
	if (bOverlapped == false && PlayerActor == PawnActorRef)
	{
		OnTrigger();
		bOverlapped = true;
	}
}