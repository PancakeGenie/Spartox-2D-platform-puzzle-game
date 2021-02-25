// Puzzle platformer game done by Vladimir Mokanj - 15.02.2021

#include "BlueBox.h"

void ABlueBox::DestroyActor(AActor* OtherActor)
{
	if (OtherActor == BluePawnActorRef)
		Destroy();
}