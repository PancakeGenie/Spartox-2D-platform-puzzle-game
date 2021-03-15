// Puzzle platformer game done by Vladimir Mokanj - 15.02.2021

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Bullet.generated.h"

UCLASS()
class SPARTOX_API ABullet : public AActor
{
	GENERATED_BODY()
	
public:	
	// Variables
	UPROPERTY(Category = "Components", BlueprintReadOnly, VisibleAnywhere)
		class UProjectileMovementComponent* BulletMovement_CPT;

	// Constructor
	ABullet();

protected:
	// Functions
	virtual void BeginPlay() override;

private:
	// Variables
	UPROPERTY(Category = "Components", BlueprintReadOnly, VisibleAnywhere, META = (AllowPrivateAccess = "true"))
		class USceneComponent* RootSceneComponent;
	UPROPERTY(Category = "Components", BlueprintReadOnly, VisibleAnywhere, META = (AllowPrivateAccess = "true"))
		class UBoxComponent* BulletDestroyCollision_COL;
	UPROPERTY(Category = "Components", BlueprintReadOnly, VisibleAnywhere, META = (AllowPrivateAccess = "true"))
		class UBoxComponent* BulletWalkOnCollision_COL;
	UPROPERTY(Category = "Components", BlueprintReadOnly, VisibleAnywhere, META = (AllowPrivateAccess = "true"))
		UStaticMeshComponent* BulletMesh_SM;

	class ASpartox_GameModeGameplay* GameModeRef;
	class ARedPawn* RedPawn;
	class ABluePawn* BluePawn;

	// Functions
	UFUNCTION()
		void OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool FromSweep, const FHitResult& Hit);
};
