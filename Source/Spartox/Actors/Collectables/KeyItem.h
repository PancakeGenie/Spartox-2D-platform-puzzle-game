// Puzzle platformer game done by Vladimir Mokanj - 15.02.2021

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "KeyItem.generated.h"

UCLASS()
class SPARTOX_API AKeyItem : public AActor
{
	GENERATED_BODY()
	
public:	
	// Constructor
	AKeyItem();

	// Functions
	virtual void Tick(float DeltaTime) override;

protected:
	// Functions
	virtual void BeginPlay() override;

private:
	// Variables
	UPROPERTY(Category = "Components", BlueprintReadOnly, VisibleAnywhere, META = (AllowPrivateAccess = "true"))
		class UBoxComponent* KeyCollision_COL;
	UPROPERTY(Category = "Components", BlueprintReadOnly, VisibleAnywhere, META = (AllowPrivateAccess = "true"))
		UStaticMeshComponent* KeyMesh_SM;

	UPROPERTY(Category = "Key Rotation", BlueprintReadWrite, EditDefaultsOnly, META = (AllowPrivateAccess = "true"))
		float fRotationSpeed{ 1.f };
	
	// Functions
	void RotateKey();

	UFUNCTION()
		void OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool FromSweep, const FHitResult& Hit);

};
