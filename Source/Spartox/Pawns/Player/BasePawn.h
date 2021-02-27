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

	UFUNCTION(BlueprintCallable)
		void SetCanPawnJump(bool canPawnJump);
	bool GetCanPawnJump();

	UFUNCTION(BlueprintCallable)
		void SetCanPawnSwitch(bool canPawnSwitch);
	bool GetCanPawnSwitch();

protected:
	// Variables
	bool isPlayerAlive{ true };
	static bool isRedPawn;

	UPROPERTY(Category = "Components", BlueprintReadOnly, VisibleAnywhere, META = (AllowPrivateAccess = "true"))
		class UBoxComponent* MeshCollision_COL;
	UPROPERTY(Category = "Components", BlueprintReadOnly, VisibleAnywhere, META = (AllowPrivateAccess = "true"))
		class UBoxComponent* DestructableBoxCollision_COL;
	UPROPERTY(Category = "Components", BlueprintReadOnly, VisibleAnywhere, META = (AllowPrivateAccess = "true"))
		UStaticMeshComponent* BaseMesh_SM;
	UPROPERTY(Category = "Components", BlueprintReadOnly, VisibleAnywhere, META = (AllowPrivateAccess = "true"))
		class USpringArmComponent* SpringArm_SA;
	UPROPERTY(Category = "Components", BlueprintReadOnly, VisibleAnywhere, META = (AllowPrivateAccess = "true"))
		class UCameraComponent* PlayerCamera_CAM;

	UPROPERTY(Category = "Components", BlueprintReadOnly, VisibleAnywhere)
		class UPawnSkills* PawnSkillsRef;

	// Functions
	virtual void BeginPlay();
	virtual void SetIsPlayerAlive(bool setIsPlayerAlive);
	virtual void SwitchPlayer();

private:
	// Variables
	UPROPERTY(Category = "Player Jump", BlueprintReadWrite, EditDefaultsOnly, META = (AllowPrivateAccess = "true"))
		bool canJump{ true };
	UPROPERTY(Category = "Player Movement", BlueprintReadWrite, EditAnywhere, META = (AllowPrivateAccess = "true"))
		float fMovementSpeed{ 800.f };
	UPROPERTY(Category = "Player Jump", BlueprintReadWrite, EditAnywhere, META = (AllowPrivateAccess = "true"))
		float fJumpForce{ 600.f };

	class ASpartox_GameModeBase* GameModeRef;
	float X_CollisionRange{ 5.f };
	float Z_CollisionRange{ 2.f };
	bool canSwitch{ true };

	// Functions
	void MoveRight(float ScaleValue);
	void Jump();
	bool MoveCollision(float& MovementDirection, float LineTrace_ZPosition);
	bool CanJump(float LineTrace_XPosition);
};