// Puzzle platformer game done by Vladimir Mokanj - 15.02.2021

#pragma once

#include "CoreMinimal.h"
#include "BaseBox.h"
#include "BlueBox.generated.h"

UCLASS()
class SPARTOX_API ABlueBox : public ABaseBox
{
	GENERATED_BODY()

protected:
	// Functions
	virtual void DestroyActor(AActor* OtherActor) override;

};
