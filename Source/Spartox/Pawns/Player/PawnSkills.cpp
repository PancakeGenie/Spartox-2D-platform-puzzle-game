// Puzzle platformer game done by Vladimir Mokanj - 15.02.2021


#include "PawnSkills.h"

// Sets default values for this component's properties
UPawnSkills::UPawnSkills()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
}

void UPawnSkills::RedPawnSpecialSkill(AActor* RedActor)
{
	if (RedActor != nullptr)
		RedActor->AddActorWorldOffset(FVector(RedActor->GetActorLocation() + 5));
}

void UPawnSkills::BluePawnSpecialSkill(AActor* BlueActor)
{

}