// Puzzle platformer game done by Vladimir Mokanj - 15.02.2021

#pragma once

#include "CoreMinimal.h"
#include "BasePlatform.h"
#include "EndPlatform.generated.h"

UCLASS()
class SPARTOX_API AEndPlatform : public ABasePlatform
{
	GENERATED_BODY()
	
public:
	// Constructor
	AEndPlatform();

protected:
	virtual void BeginPlay() override;

private:
	// Variables
	UPROPERTY(Category = "Components", BlueprintReadOnly, VisibleAnywhere, META = (AllowPrivateAccess = "true"))
		class UBoxComponent* EndLevelCollision_COL;

	class ASpartox_GameModeGameplay* GameModeRef;

	// Functions
	UFUNCTION()
		void OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool FromSweep, const FHitResult& Hit);
};
