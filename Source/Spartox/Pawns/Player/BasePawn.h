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

	void SetDefaltPlayer(bool isCurrentlyRedPlayer = false);

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

	UPROPERTY(Category = "HUD and UI", EditDefaultsOnly, BlueprintReadOnly)
		TSubclassOf<class UUserWidget> ToggleWidgetClass;
	UPROPERTY(Category = "HUD and UI", EditDefaultsOnly, BlueprintReadOnly)
		class UUserWidget* ToggleMenuRef;

	// Functions
	virtual void BeginPlay();
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

	class ASpartox_GameModeGameplay* GameModeRef;
	float X_CollisionRange{ 5.f };
	float Z_CollisionRange{ 2.f };

	UPROPERTY(Category = "HUD and UI", BlueprintReadWrite, EditAnywhere, META = (AllowPrivateAccess = "true"))
		bool IsToggleMenu{ false };

	// Functions
	void MoveRight(float ScaleValue);
	void Jump();
	bool MoveCollision(float& MovementDirection);
	bool CanJump();
	void Reset();
	void ToggleMenu();
	void ToggleMenuInit();
};