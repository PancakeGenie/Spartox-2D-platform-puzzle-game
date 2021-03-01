// Puzzle platformer game done by Vladimir Mokanj - 15.02.2021

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PawnSkills.generated.h"


UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class SPARTOX_API UPawnSkills : public UActorComponent
{
	GENERATED_BODY()

public:
	// Constructor
	UPawnSkills();
};
