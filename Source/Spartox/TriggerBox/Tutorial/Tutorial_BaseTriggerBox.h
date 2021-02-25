// Puzzle platformer game done by Vladimir Mokanj - 15.02.2021

#pragma once

#include "CoreMinimal.h"
#include "Engine/TriggerBox.h"
#include "Tutorial_BaseTriggerBox.generated.h"

UCLASS()
class SPARTOX_API ATutorial_BaseTriggerBox : public ATriggerBox
{
	GENERATED_BODY()

protected:
	// Variables
	bool bOverlapped{ false };

	// Functions
	virtual void BeginPlay();

	UFUNCTION(BlueprintImplementableEvent)
		void OnTrigger();

private:
	// Functions
	UFUNCTION()
		void OnOverlap(AActor* OtherActor, AActor* PlayerActor);
};
