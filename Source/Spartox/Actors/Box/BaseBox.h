// Puzzle platformer game done by Vladimir Mokanj - 15.02.2021

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseBox.generated.h"

UCLASS()
class SPARTOX_API ABaseBox : public AActor
{
	GENERATED_BODY()

public:
	// Constructor
	ABaseBox();

protected:
	// Variables
	class AActor* RedPawnActorRef;
	class AActor* BluePawnActorRef;

	// Functions
	virtual void BeginPlay() override;
	virtual void DestroyActor(AActor* OtherActor);

	UFUNCTION()
		void OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool FromSweep, const FHitResult& Hit);

private:
	// Variables
	UPROPERTY(Category = "Components", BlueprintReadOnly, VisibleAnywhere, META = (AllowPrivateAccess = "true"))
		class UBoxComponent* BoxCollision_COL;
	UPROPERTY(Category = "Components", BlueprintReadOnly, VisibleAnywhere, META = (AllowPrivateAccess = "true"))
		UStaticMeshComponent* BoxMesh_SM;
};
