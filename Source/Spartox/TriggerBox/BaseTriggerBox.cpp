// Puzzle platformer game done by Vladimir Mokanj - 15.02.2021

#include "BaseTriggerBox.h"
#include "Kismet/GameplayStatics.h"
#include "../Pawns/Player/BluePawn.h"
#include "../Pawns/Player/RedPawn.h"
#include "../Global_Log.h"

DEFINE_LOG_CATEGORY_STATIC(TriggerBoxLog, All, All)

void ABaseTriggerBox::BeginPlay()
{
	// Cast players
	RedPawn = Cast<ARedPawn>(UGameplayStatics::GetActorOfClass(GetWorld(), ARedPawn::StaticClass()));
	BluePawn = Cast<ABluePawn>(UGameplayStatics::GetActorOfClass(GetWorld(), ABluePawn::StaticClass()));

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
		// Check trigger box was overlapped and if overlapping actor was player pawn
		if (PlayerActor == BluePawn || PlayerActor == RedPawn)
			OnTriggerOverlap();			// Blueprint implementation
	}
}

void ABaseTriggerBox::OnOverlapEnd(AActor* OtherActor, AActor* PlayerActor)
{
	if (bMultipleOverlaps == true)
	{
		// Check trigger box was overlapped and if overlapping actor was player pawn
		if (PlayerActor == BluePawn || PlayerActor == RedPawn)
			OnTriggerEndOverlap();			// Blueprint implementation
	}
}
// ------------------------------------------------------------------------------------------------------------------------------