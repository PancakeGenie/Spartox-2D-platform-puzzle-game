// Puzzle platformer game done by Vladimir Mokanj - 15.02.2021


#include "BasePawn.h"
#include "Components/BoxComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "../../GameMode/Spartox_GameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "PawnSkills.h"
#include "DrawDebugHelpers.h"

// Static variable
bool ABasePawn::isRedPawn{ false };

// Sets default values
ABasePawn::ABasePawn()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Create all objects and link them
	// ---------------------------------
	// Responsible for collision detection
	MeshCollision_COL = CreateDefaultSubobject<UBoxComponent>(TEXT("Mesh Collision"));
	RootComponent = MeshCollision_COL;

	// Visible mesh to player
	BaseMesh_SM = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Player Mesh"));
	BaseMesh_SM->AttachToComponent(RootComponent, FAttachmentTransformRules::SnapToTargetIncludingScale);

	// Responsible for interacting with other Actors in level
	DestructableBoxCollision_COL = CreateDefaultSubobject<UBoxComponent>(TEXT("Obstacle Collision"));
	DestructableBoxCollision_COL->AttachToComponent(RootComponent, FAttachmentTransformRules::SnapToTargetIncludingScale);

	// Responsible for determining Camera position and interaction
	SpringArm_SA = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
	SpringArm_SA->AttachToComponent(RootComponent, FAttachmentTransformRules::SnapToTargetNotIncludingScale);

	// Responsible for seeing the game. It's a camera...
	PlayerCamera_CAM = CreateDefaultSubobject<UCameraComponent>(TEXT("Player Camera"));
	PlayerCamera_CAM->AttachToComponent(SpringArm_SA, FAttachmentTransformRules::SnapToTargetNotIncludingScale);

	// Responsible for skills in the game
	PawnSkillsRef = CreateDefaultSubobject<UPawnSkills>(TEXT("Player Skills"));
}

void ABasePawn::BeginPlay()
{
	GameModeRef = Cast<ASpartox_GameModeBase>(UGameplayStatics::GetGameMode(this));
}

// ------------------------------------------------------------------------------------------------------------------------------
// Player input -----------------------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------------------------------------
void ABasePawn::SetupPlayerInputComponent(UInputComponent* PlayerInput)
{
	Super::SetupPlayerInputComponent(PlayerInput);

	PlayerInput->BindAxis("MoveRight", this, &ABasePawn::MoveRight);
	PlayerInput->BindAction("Jump", EInputEvent::IE_Pressed, this, &ABasePawn::Jump);
	PlayerInput->BindAction("Switch", EInputEvent::IE_Pressed, this, &ABasePawn::SwitchPlayer);
}
// ------------------------------------------------------------------------------------------------------------------------------

// ------------------------------------------------------------------------------------------------------------------------------
// Player movement and jump -----------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------------------------------------
void ABasePawn::MoveRight(float ScaleValue)
{
	if (ScaleValue != 0.f && canMove == true && isPlayerAlive == true)
	{
		// Checker, responsible for determining if player can move. 
		if (MoveCollision(ScaleValue, -MeshCollision_COL->GetScaledBoxExtent().Z) == true || MoveCollision(ScaleValue, MeshCollision_COL->GetScaledBoxExtent().Z) == true)
			return;

		const FVector vCalcMovement{ GetWorld()->GetDeltaSeconds() * ScaleValue * fMovementSpeed, 0.f, 0.f };
		AddActorWorldOffset(vCalcMovement);
	}
}

// Function that returns true if collision happened on map. Prevents player from "bugging" out inside objects.
bool ABasePawn::MoveCollision(float& MovementDirection, float LineTrace_ZPosition)
{
	FHitResult HitCollision;
	FVector StartLocation{ RootComponent->GetComponentLocation().X, 0.f, RootComponent->GetComponentLocation().Z - LineTrace_ZPosition + 0.1f };
	FVector EndLocation;
	FCollisionQueryParams TraceParams;

	// End length of vector depends on MovementDirection vector (basically if player is moving right, EndLocation should be right of player)
	MovementDirection > 0 ? EndLocation = FVector(StartLocation.X + MeshCollision_COL->GetScaledBoxExtent().X + X_CollisionRange, 0.f, StartLocation.Z)
						  : EndLocation = FVector(StartLocation.X - MeshCollision_COL->GetScaledBoxExtent().X - X_CollisionRange, 0.f, StartLocation.Z);

	TraceParams.AddIgnoredActor(this);

	// For testing purposes only.
	//DrawDebugLine(GetWorld(), StartLocation, EndLocation, FColor::Red, false, 2.f);

	return GetWorld()->LineTraceSingleByChannel(HitCollision, StartLocation, EndLocation, ECC_Pawn, TraceParams);
}

void ABasePawn::Jump()
{
	if (isPlayerAlive == true && canJump == true)
	{	
		// Checker, responsible for determining if player can jump. 
		if (CanJump(-MeshCollision_COL->GetScaledBoxExtent().Z) == false && CanJump(MeshCollision_COL->GetScaledBoxExtent().Z) == false)
			return;

		const FVector vCalcJump{ 0.f, 0.f, fJumpForce };
		MeshCollision_COL->AddImpulse(vCalcJump, NAME_None, true);
	}
}

// Function that returns true if collision happened on map. Allows player to jump again.
bool ABasePawn::CanJump(float LineTrace_XPosition)
{
	FHitResult HitCollision;
	FVector StartLocation{ RootComponent->GetComponentLocation().X - LineTrace_XPosition, 0.f, RootComponent->GetComponentLocation().Z};
	FVector EndLocation{StartLocation.X, 0.f, StartLocation.Z - MeshCollision_COL->GetScaledBoxExtent().Z - Z_CollisionRange };
	FCollisionQueryParams TraceParams;

	TraceParams.AddIgnoredActor(this);

	// For testing purposes only.
	//DrawDebugLine(GetWorld(), StartLocation, EndLocation, FColor::Blue, false, 2.f);

	return GetWorld()->LineTraceSingleByChannel(HitCollision, StartLocation, EndLocation, ECC_Pawn, TraceParams);
}
// ------------------------------------------------------------------------------------------------------------------------------

// ------------------------------------------------------------------------------------------------------------------------------
// Player switch ----------------------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------------------------------------
void ABasePawn::SwitchPlayer()
{
	if (isPlayerAlive == true && canSwitch == true)
		GameModeRef->SwitchPlayer(ABasePawn::isRedPawn);
}
// ------------------------------------------------------------------------------------------------------------------------------

void ABasePawn::SetIsPlayerAlive(bool setIsPlayerAlive)
{
	isPlayerAlive = setIsPlayerAlive;
}


// ------------------------------------------------------------------------------------------------------------------------------
// Getter/Setters ---------------------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------------------------------------
// Jump 
void ABasePawn::SetCanPlayerJump(bool canPlayerJump)
{
	canJump = canPlayerJump;
}

bool ABasePawn::GetCanPlayerJump()
{
	return canJump;
}

// Switch player
void ABasePawn::SetCanPlayerSwitch(bool canPlayerSwitch)
{
	canSwitch = canPlayerSwitch;
}

bool ABasePawn::GetCanPlayerSwitch()
{
	return canSwitch;
}

// Move player
void ABasePawn::SetCanPlayerMove(bool canPlayerMove)
{
	canMove = canPlayerMove;
}

bool ABasePawn::GetCanPlayerMove()
{
	return canMove;
}
// ------------------------------------------------------------------------------------------------------------------------------