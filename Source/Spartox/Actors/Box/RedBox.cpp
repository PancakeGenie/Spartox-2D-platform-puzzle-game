// Puzzle platformer game done by Vladimir Mokanj - 15.02.2021

#include "RedBox.h"
#include "Kismet/GameplayStatics.h"
#include "../../Pawns/Player/RedPawn.h"

// ------------------------------------------------------------------------------------------------------------------------------
// Actor interaction on hit -----------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------------------------------------
void ARedBox::DestroyActor(AActor* OtherActor)
{
	AActor* RedPawnActorRef = UGameplayStatics::GetActorOfClass(GetWorld(), ARedPawn::StaticClass());

	if (OtherActor == RedPawnActorRef)
		Destroy();
}
// ------------------------------------------------------------------------------------------------------------------------------