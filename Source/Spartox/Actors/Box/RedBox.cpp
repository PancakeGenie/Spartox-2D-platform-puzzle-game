// Puzzle platformer game done by Vladimir Mokanj - 15.02.2021

#include "RedBox.h"

void ARedBox::DestroyActor(AActor* OtherActor)
{
	if (OtherActor == RedPawnActorRef)
		Destroy();
}