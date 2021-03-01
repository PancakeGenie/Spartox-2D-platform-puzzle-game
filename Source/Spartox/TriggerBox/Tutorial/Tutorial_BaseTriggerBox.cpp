// Puzzle platformer game done by Vladimir Mokanj - 15.02.2021

#include "Tutorial_BaseTriggerBox.h"
#include "Kismet/GameplayStatics.h"
#include "Components/WidgetComponent.h"

ATutorial_BaseTriggerBox::ATutorial_BaseTriggerBox()
{
	// Create components and link them
	BaseMesh_SM = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Helper Mesh"));
	BaseMesh_SM->AttachToComponent(RootComponent, FAttachmentTransformRules::SnapToTargetNotIncludingScale);

	TextWidget_WGT = CreateDefaultSubobject<UWidgetComponent>(TEXT("Text Widget"));
	TextWidget_WGT->AttachToComponent(BaseMesh_SM, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
}

void ATutorial_BaseTriggerBox::BeginPlay()
{
	// Dynamic (OnOverlap)
	OnActorBeginOverlap.AddDynamic(this, &ATutorial_BaseTriggerBox::OnOverlapBegin);
	OnActorEndOverlap.AddDynamic(this, &ATutorial_BaseTriggerBox::OnOverlapEnd);
}
// ------------------------------------------------------------------------------------------------------------------------------

// ------------------------------------------------------------------------------------------------------------------------------
// Trigger overlap function -----------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------------------------------------
void ATutorial_BaseTriggerBox::OnOverlapBegin(AActor* OtherActor, AActor* PlayerActor)
{
	// Cast Pawn
	AActor* PawnActorRef = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);

	// Check trigger box was overlapped and if overlapping actor was player pawn
	if (bMultipleOverlaps == true && PlayerActor == PawnActorRef)
	{
		OnTriggerOverlap();			// Blueprint implementation
	}
}

void ATutorial_BaseTriggerBox::OnOverlapEnd(AActor* OtherActor, AActor* PlayerActor)
{
	// Cast Pawn
	AActor* PawnActorRef = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);

	// Check trigger box was overlapped and if overlapping actor was player pawn
	if (bMultipleOverlaps == true && PlayerActor == PawnActorRef)
	{
		OnTriggerEndOverlap();			// Blueprint implementation
	}
}
// ------------------------------------------------------------------------------------------------------------------------------