// Puzzle platformer game done by Vladimir Mokanj - 15.02.2021

#pragma once

#include "CoreMinimal.h"
#include "Engine/TriggerBox.h"
#include "Tutorial_BaseTriggerBox.generated.h"

UCLASS()
class SPARTOX_API ATutorial_BaseTriggerBox : public ATriggerBox
{
	GENERATED_BODY()

public:
	// Constructor
	ATutorial_BaseTriggerBox();

protected:
	// Functions
	virtual void BeginPlay();

	UFUNCTION(BlueprintImplementableEvent)
		void OnTriggerOverlap();
	UFUNCTION(BlueprintImplementableEvent)
		void OnTriggerEndOverlap();

private:
	// Variables
	UPROPERTY(Category = "Components", BlueprintReadOnly, VisibleAnywhere, META = (AllowPrivateAccess = "true"))
		UStaticMeshComponent* BaseMesh_SM;
	UPROPERTY(Category = "Components", BlueprintReadOnly, VisibleAnywhere, META = (AllowPrivateAccess = "true"))
		class UWidgetComponent* TextWidget_WGT;
	UPROPERTY(Category = "Interaction", EditDefaultsOnly, BlueprintReadWrite, META = (AllowPrivateAccess = "true"));
		bool bMultipleOverlaps{ true };

	// Functions
	UFUNCTION()
		void OnOverlapBegin(AActor* OtherActor, AActor* PlayerActor);
	UFUNCTION()
		void OnOverlapEnd(AActor* OtherActor, AActor* PlayerActor);
};
