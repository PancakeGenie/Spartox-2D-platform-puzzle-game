// Puzzle platformer game done by Vladimir Mokanj - 15.02.2021

#include "BaseTriggerBox.h"
#include "Kismet/GameplayStatics.h"
#include "../Global_Log.h"

DEFINE_LOG_CATEGORY_STATIC(TriggerBoxLog, All, All)

void ABaseTriggerBox::BeginPlay()
{
	// Dynamic (OnOverlap) delegate
	OnActorBeginOverlap.AddDynamic(this, &ABaseTriggerBox::OnOverlapBegin);
	OnActorEndOverlap.AddDynamic(this, &ABaseTriggerBox::OnOverlapEnd);
}
// ------------------------------------------------------------------------------------------------------------------------------

// ------------------------------------------------------------------------------------------------------------------------------
// Trigger on overlap functions -------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------------------------------------
void ABaseTriggerBox::OnOverlapBegin(AActor* OtherActor, AActor* PlayerActor)
{
	if (bMultipleOverlaps == true)
	{
		AActor* PawnActorRef = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);

		// Check trigger box was overlapped and if overlapping actor was player pawn
		if (PlayerActor == PawnActorRef)
			OnTriggerOverlap();			// Blueprint implementation
	}
}

void ABaseTriggerBox::OnOverlapEnd(AActor* OtherActor, AActor* PlayerActor)
{
	if (bMultipleOverlaps == true)
	{
		AActor* PawnActorRef = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);

		// Check trigger box was overlapped and if overlapping actor was player pawn
		if (PlayerActor == PawnActorRef)
			OnTriggerEndOverlap();			// Blueprint implementation
	}
}
// ------------------------------------------------------------------------------------------------------------------------------