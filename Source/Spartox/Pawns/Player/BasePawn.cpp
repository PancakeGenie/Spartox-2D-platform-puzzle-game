// Puzzle platformer game done by Vladimir Mokanj - 15.02.2021


#include "BasePawn.h"
#include "Components/BoxComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "../../GameMode/Spartox_GameModeGameplay.h"
#include "Kismet/GameplayStatics.h"
#include "PawnSkills.h"
#include "DrawDebugHelpers.h"
#include "Blueprint/UserWidget.h"
#include "../../Widgets/ToggleMenu.h"

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

	// Cast widget blueprint (reflection)
	static ConstructorHelpers::FObjectFinder<UBlueprint> ToggleMenu_BP(TEXT("WidgetBlueprint'/Game/Blueprints/Widgets/Game/ToggleMenu_WBP.ToggleMenu_WBP'"));
	if (ToggleMenu_BP.Object != nullptr)
		ToggleWidgetClass = (UClass*)ToggleMenu_BP.Object->GeneratedClass;
}

void ABasePawn::BeginPlay()
{
	Super::BeginPlay();

	GameModeRef = Cast<ASpartox_GameModeGameplay>(UGameplayStatics::GetGameMode(this));

	ToggleMenuInit();
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
	PlayerInput->BindAction("Reset", EInputEvent::IE_Pressed, this, &ABasePawn::Reset);
	PlayerInput->BindAction("Menu", EInputEvent::IE_Pressed, this, &ABasePawn::ToggleMenu);
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
		if (CanJump(-MeshCollision_COL->GetScaledBoxExtent().Z) == false && 
			CanJump(MeshCollision_COL->GetScaledBoxExtent().Z) == false && 
			CanJump(0) == false)
			return;

		const FVector vCalcJump{ 0.f, 0.f, fJumpForce };

		MeshCollision_COL->SetAllPhysicsLinearVelocity(FVector(0, 0, 0), false);
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
// Player switch and reset ------------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------------------------------------
void ABasePawn::SwitchPlayer()
{
	if (isPlayerAlive == true && canSwitch == true)
		GameModeRef->SwitchPlayer(ABasePawn::isRedPawn);
}

void ABasePawn::Reset()
{
	GameModeRef->ResetCurrentLevel();
}
// ------------------------------------------------------------------------------------------------------------------------------

// ------------------------------------------------------------------------------------------------------------------------------
// Player game menu -------------------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------------------------------------
void ABasePawn::ToggleMenu()
{
	if (IsToggleMenu == false)
	{
		ToggleWidgetRef->SetVisibility(ESlateVisibility::Visible);
		UGameplayStatics::GetPlayerController(GetWorld(), 0)->SetInputMode(FInputModeUIOnly());
		UGameplayStatics::GetPlayerController(GetWorld(), 0)->bShowMouseCursor = true;
		UGameplayStatics::SetGamePaused(GetWorld(), true);
		IsToggleMenu = true;
	}
}

void ABasePawn::ToggleMenuInit()
{
	ToggleWidgetRef = CreateWidget<UToggleMenu>(GetWorld(), ToggleWidgetClass);
	if (ToggleWidgetRef == nullptr)
		return;

	ToggleWidgetRef->AddToViewport();						  // Add widget to viewport
	ToggleWidgetRef->SetVisibility(ESlateVisibility::Hidden); // Set it to hidden so its not open on spawn.
}

// ------------------------------------------------------------------------------------------------------------------------------
// Getter/Setters ---------------------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------------------------------------
// Move player
void ABasePawn::SetCanPlayerMove(bool canPlayerMove)
{
	canMove = canPlayerMove;
}

bool ABasePawn::GetCanPlayerMove()
{
	return canMove;
}

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

// Default player
void ABasePawn::SetDefaltPlayer(bool isCurrentlyRedPlayer)
{
	ABasePawn::isRedPawn = isCurrentlyRedPlayer;
}
// ------------------------------------------------------------------------------------------------------------------------------