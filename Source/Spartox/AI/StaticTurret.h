// Puzzle platformer game done by Vladimir Mokanj - 15.02.2021

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "StaticTurret.generated.h"

UCLASS()
class SPARTOX_API AStaticTurret : public AActor
{
	GENERATED_BODY()
	
public:	
	// Constructor
	AStaticTurret();

protected:
	// Functions
	virtual void BeginPlay() override;

private:
	// Variables
	UPROPERTY(Category = "Components", BlueprintReadOnly, VisibleAnywhere, META = (AllowPrivateAccess = "true"))
		class UBoxComponent* CannonCollision_COL;
	UPROPERTY(Category = "Components", BlueprintReadOnly, VisibleAnywhere, META = (AllowPrivateAccess = "true"))
		UStaticMeshComponent* CannonBaseMesh_SM;
	UPROPERTY(Category = "Components", BlueprintReadOnly, VisibleAnywhere, META = (AllowPrivateAccess = "true"))
		UStaticMeshComponent* CannonMesh_SM;
	UPROPERTY(Category = "Components", BlueprintReadOnly, VisibleAnywhere, META = (AllowPrivateAccess = "true"))
		class UArrowComponent* BulletArrow_ARW;

	UPROPERTY(Category = "Bullet", BlueprintReadOnly, EditAnywhere, META = (AllowPrivateAccess = "true"))
		float BulletSpawnDelay{ 2.5f };

	FTimerHandle BulletSpawnTimer;
	TSubclassOf<class ABullet> Bullet;

	// Functions
	void SpawnBullet();
};
