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
		void SetCanPlayerJump(bool canPlayerJump);
	bool GetCanPlayerJump();

	UFUNCTION(BlueprintCallable)
		void SetCanPlayerSwitch(bool canPlayerSwitch);
	bool GetCanPlayerSwitch();

	UFUNCTION(BlueprintCallable)
		void SetCanPlayerMove(bool canPlayerMove);
	bool GetCanPlayerMove();

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
	UPROPERTY(Category = "Player Jump", BlueprintReadWrite, EditAnywhere, META = (AllowPrivateAccess = "true"))
		float fJumpForce{ 500.f };
	UPROPERTY(Category = "Player Movement", BlueprintReadWrite, EditDefaultsOnly, META = (AllowPrivateAccess = "true"))
		bool canMove{ true };
	UPROPERTY(Category = "Player Movement", BlueprintReadWrite, EditAnywhere, META = (AllowPrivateAccess = "true"))
		float fMovementSpeed{ 600.f };
	UPROPERTY(Category = "Player Switch", BlueprintReadWrite, EditDefaultsOnly, META = (AllowPrivateAccess = "true"))
		bool canSwitch{ true };

	class ASpartox_GameModeBase* GameModeRef;
	float X_CollisionRange{ 5.f };
	float Z_CollisionRange{ 2.f };

	// Functions
	void MoveRight(float ScaleValue);
	void Jump();
	bool MoveCollision(float& MovementDirection, float LineTrace_ZPosition);
	bool CanJump(float LineTrace_XPosition);
};