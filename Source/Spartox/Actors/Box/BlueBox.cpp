// Puzzle platformer game done by Vladimir Mokanj - 15.02.2021

#include "BlueBox.h"
#include "Kismet/GameplayStatics.h"
#include "../../Pawns/Player/BluePawn.h"

// ------------------------------------------------------------------------------------------------------------------------------
// Actor interaction on hit -----------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------------------------------------
void ABlueBox::DestroyActor(AActor* OtherActor)
{
	AActor* BluePawnActorRef = UGameplayStatics::GetActorOfClass(GetWorld(), ABluePawn::StaticClass());

	if (OtherActor == BluePawnActorRef)
		Destroy();
}
// ------------------------------------------------------------------------------------------------------------------------------