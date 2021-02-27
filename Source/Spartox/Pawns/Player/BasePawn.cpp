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
	PrimaryActorTick.bCanEverTick = false;

	// Create objects and link them
	MeshCollision_COL = CreateDefaultSubobject<UBoxComponent>(TEXT("Mesh Collision"));
	RootComponent = MeshCollision_COL;

	BaseMesh_SM = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Player Mesh"));
	BaseMesh_SM->AttachToComponent(RootComponent, FAttachmentTransformRules::SnapToTargetIncludingScale);

	DestructableBoxCollision_COL = CreateDefaultSubobject<UBoxComponent>(TEXT("Obstacle Collision"));
	DestructableBoxCollision_COL->AttachToComponent(RootComponent, FAttachmentTransformRules::SnapToTargetIncludingScale);

	SpringArm_SA = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
	SpringArm_SA->AttachToComponent(RootComponent, FAttachmentTransformRules::SnapToTargetIncludingScale);

	PlayerCamera_CAM = CreateDefaultSubobject<UCameraComponent>(TEXT("Player Camera"));
	PlayerCamera_CAM->AttachToComponent(SpringArm_SA, FAttachmentTransformRules::SnapToTargetIncludingScale);

	PawnSkillsRef = CreateDefaultSubobject<UPawnSkills>(TEXT("Player Skills"));
}

void ABasePawn::BeginPlay()
{
	// Assign game mode ref to GameModeRef handle
	GameModeRef = Cast<ASpartox_GameModeBase>(UGameplayStatics::GetGameMode(this));
}

// ------------------------------------------------------------------------------------------------------------------------------
// Player movement and jump -----------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------------------------------------
void ABasePawn::SetupPlayerInputComponent(UInputComponent* PlayerInput)
{
	Super::SetupPlayerInputComponent(PlayerInput);

	// Link player movement, jump and switch
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
	if (ScaleValue != 0.f && isPlayerAlive == true)
	{
		if (MoveCollision(ScaleValue, -MeshCollision_COL->GetScaledBoxExtent().Z) == true || MoveCollision(ScaleValue, MeshCollision_COL->GetScaledBoxExtent().Z) == true)
		{
			//UE_LOG(LogTemp, Warning, TEXT("Collision while moving!"));
			return;
		}

		// Movement is based on frame rate (DeltaSeconds), scale value (Movement direction) and MovementSpeed (Arbitrary value)
		const FVector vCalcMovement{ GetWorld()->GetDeltaSeconds() * ScaleValue * fMovementSpeed, 0.f, 0.f };

		// Move player
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

	// Direction and length of end vector
	if (MovementDirection > 0)
		EndLocation = FVector(StartLocation.X + MeshCollision_COL->GetScaledBoxExtent().X + X_CollisionRange, 0.f, StartLocation.Z);
	else
		EndLocation = FVector(StartLocation.X - MeshCollision_COL->GetScaledBoxExtent().X - X_CollisionRange, 0.f, StartLocation.Z);

	//DrawDebugLine(GetWorld(), StartLocation, EndLocation, FColor::Red, false, 2.f);
	return GetWorld()->LineTraceSingleByChannel(HitCollision, StartLocation, EndLocation, ECC_Visibility, TraceParams);
}

void ABasePawn::Jump()
{
	if (isPlayerAlive == true && canJump == true)
	{
		if (CanJump(-MeshCollision_COL->GetScaledBoxExtent().Z) == false && CanJump(MeshCollision_COL->GetScaledBoxExtent().Z) == false)
		{
			//UE_LOG(LogTemp, Warning, TEXT("No collision, player is in air"));
			return;
		}

		// Jump is based on fJumpForce
		const FVector vCalcJump{ 0.f, 0.f, fJumpForce };

		// Jump, ignore player mass
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

	//DrawDebugLine(GetWorld(), StartLocation, EndLocation, FColor::Blue, false, 2.f);
	return GetWorld()->LineTraceSingleByChannel(HitCollision, StartLocation, EndLocation, ECC_Visibility, TraceParams);
}
// ------------------------------------------------------------------------------------------------------------------------------

// ------------------------------------------------------------------------------------------------------------------------------
// Player switch ----------------------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------------------------------------
void ABasePawn::SwitchPlayer()
{
	if (isPlayerAlive == true)
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
void ABasePawn::SetCanPawnJump(bool canPawnJump)
{
	canJump = canPawnJump;
}

bool ABasePawn::GetCanPawnJump()
{
	return canJump;
}

// Switch player
void ABasePawn::SetCanPawnSwitch(bool canPawnSwitch)
{
	canSwitch = canPawnSwitch;
}

bool ABasePawn::GetCanPawnSwitch()
{
	return canSwitch;
}