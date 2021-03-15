// Puzzle platformer game done by Vladimir Mokanj - 15.02.2021

#pragma once

#include "CoreMinimal.h"
#include "Engine/TriggerBox.h"
#include "BaseTriggerBox.generated.h"

UCLASS()
class SPARTOX_API ABaseTriggerBox : public ATriggerBox
{
	GENERATED_BODY()

protected:
	// Functions
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintImplementableEvent)
		void OnTriggerOverlap();
	UFUNCTION(BlueprintImplementableEvent)
		void OnTriggerEndOverlap();

private:
	// Variables
	UPROPERTY(Category = "Interaction", EditDefaultsOnly, BlueprintReadWrite, META = (AllowPrivateAccess = "true"));
	bool bMultipleOverlaps{ true };

	class ARedPawn* RedPawn;
	class ABluePawn* BluePawn;

	// Functions
	UFUNCTION()
		void OnOverlapBegin(AActor* OtherActor, AActor* PlayerActor);
	UFUNCTION()
		void OnOverlapEnd(AActor* OtherActor, AActor* PlayerActor);
};
