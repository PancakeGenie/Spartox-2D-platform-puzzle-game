// Puzzle platformer game done by Vladimir Mokanj - 15.02.2021

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "BasePawn.generated.h"

UCLASS()
class SPARTOX_API ABasePawn : public APawn
{
	GENERATED_BODY()

public:
	// Constructor
	ABasePawn();

	// Functions
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInput) override;

protected:
	// Variables
	bool isPlayerAlive;
	bool canJump;

	UPROPERTY(Category = "Components", BlueprintReadOnly, VisibleAnywhere)
		class UPawnSkills* PawnSkillsRef;

	// Functions
	virtual void BeginPlay();
	virtual void SetIsPlayerAlive(bool setIsPlayerAlive);

private:
	// Variables
	UPROPERTY(Category = "Components", BlueprintReadOnly, VisibleAnywhere, META = (AllowPrivateAccess = "true"))
		class UBoxComponent* MeshCollision_COL;
	UPROPERTY(Category = "Components", BlueprintReadOnly, VisibleAnywhere, META = (AllowPrivateAccess = "true"))
		UStaticMeshComponent* BaseMesh_SM;
	UPROPERTY(Category = "Components", BlueprintReadOnly, VisibleAnywhere, META = (AllowPrivateAccess = "true"))
		class USpringArmComponent* SpringArm_SA;
	UPROPERTY(Category = "Components", BlueprintReadOnly, VisibleAnywhere, META = (AllowPrivateAccess = "true"))
		class UCameraComponent* PlayerCamera_CAM;

	UPROPERTY(Category = "Player Jump", BlueprintReadWrite, EditDefaultsOnly, META = (AllowPrivateAccess = "true"))
		bool isJumping{ false };
	UPROPERTY(Category = "Player Movement", BlueprintReadWrite, EditAnywhere, META = (AllowPrivateAccess = "true"))
		float fMovementSpeed{ 800.f };
	UPROPERTY(Category = "Player Jump", BlueprintReadWrite, EditAnywhere, META = (AllowPrivateAccess = "true"))
		float fJumpForce{ 600.f };

	class ASpartox_GameModeBase* GameModeRef;

	// Functions
	void MoveRight(float ScaleValue);
	void Jump();
	void SwitchPlayer();

	UFUNCTION()
		void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
};
