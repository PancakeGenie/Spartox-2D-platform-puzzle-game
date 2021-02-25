// Puzzle platformer game done by Vladimir Mokanj - 15.02.2021

#pragma once

#include "CoreMinimal.h"
#include "BaseBox.h"
#include "RedBox.generated.h"

UCLASS()
class SPARTOX_API ARedBox : public ABaseBox
{
	GENERATED_BODY()

protected:
	virtual void DestroyActor(AActor* OtherActor) override;
};
