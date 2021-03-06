// Puzzle platformer game done by Vladimir Mokanj - 15.02.2021


#include "BasePawn.h"
#include "Components/BoxComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"
#include "Blueprint/UserWidget.h"

#include "../../GameMode/Spartox_GameModeGameplay.h"

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
	BaseMesh_SM->SetupAttachment(RootComponent);

	// Responsible for interacting with other Actors in level
	DestructableBoxCollision_COL = CreateDefaultSubobject<UBoxComponent>(TEXT("Obstacle Collision"));
	DestructableBoxCollision_COL->SetupAttachment(RootComponent);

	// Responsible for determining Camera position and interaction
	SpringArm_SA = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
	SpringArm_SA->SetupAttachment(RootComponent);

	// Responsible for seeing the game. It's a camera...
	PlayerCamera_CAM = CreateDefaultSubobject<UCameraComponent>(TEXT("Player Camera"));
	PlayerCamera_CAM->SetupAttachment(SpringArm_SA);

	// Cast widget blueprint (reflection)
	static ConstructorHelpers::FObjectFinder<UClass> ToggleMenu_BP(TEXT("Class'/Game/Blueprints/Widgets/Game/ToggleMenu_WBP.ToggleMenu_WBP_C'"));
	if (ToggleMenu_BP.Object != nullptr)
		ToggleWidgetClass = ToggleMenu_BP.Object;
}

void ABasePawn::BeginPlay()
{
	Super::BeginPlay();

	GameModeRef = Cast<ASpartox_GameModeGameplay>(UGameplayStatics::GetGameMode(this));

	// Create in game menu and hide it
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
	PlayerInput->BindAction("Menu", EInputEvent::IE_Released, this, &ABasePawn::ToggleMenu);
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
		if (MoveCollision(ScaleValue) == true)
			return;

		const FVector vCalcMovement{ GetWorld()->GetDeltaSeconds() * ScaleValue * fMovementSpeed, 0.f, 0.f };
		AddActorWorldOffset(vCalcMovement);
	}
}

// Function that returns true if collision happened on map. Prevents player from "bugging" out inside objects.
bool ABasePawn::MoveCollision(float& MovementDirection)
{
	FHitResult HitCollision;
	FVector StartLocation;
	FVector EndLocation;
	FCollisionQueryParams TraceParams;

	// End length of vector depends on MovementDirection vector (basically if player is moving right, EndLocation should be right of player)
	MovementDirection > 0 ? StartLocation = FVector(RootComponent->GetComponentLocation().X + MeshCollision_COL->GetScaledBoxExtent().X + X_CollisionRange, 0.f, RootComponent->GetComponentLocation().Z + MeshCollision_COL->GetScaledBoxExtent().Z)
						  : StartLocation = FVector(RootComponent->GetComponentLocation().X - MeshCollision_COL->GetScaledBoxExtent().X - X_CollisionRange, 0.f, RootComponent->GetComponentLocation().Z + MeshCollision_COL->GetScaledBoxExtent().Z);

	EndLocation = FVector(StartLocation.X, 0.f, StartLocation.Z - (2 * MeshCollision_COL->GetScaledBoxExtent().Z) + 0.1f);

	// For testing purposes only.
	//DrawDebugLine(GetWorld(), StartLocation, EndLocation, FColor::Red, false, 500.f);

	return GetWorld()->LineTraceSingleByChannel(HitCollision, StartLocation, EndLocation, ECC_Pawn, TraceParams);
}

void ABasePawn::Jump()
{
	if (isPlayerAlive == true && canJump == true)
	{	
		// Checker, responsible for determining if player can jump. 
		if (CanJump() == false)
			return;

		const FVector vCalcJump{ 0.f, 0.f, fJumpForce };

		MeshCollision_COL->SetAllPhysicsLinearVelocity(FVector(0, 0, 0), false);
		MeshCollision_COL->AddImpulse(vCalcJump, NAME_None, true);
	}
}

// Function that returns true if collision happened on map. Allows player to jump again.
bool ABasePawn::CanJump()
{
	FHitResult HitCollision;
	FVector StartLocation{ RootComponent->GetComponentLocation().X - MeshCollision_COL->GetScaledBoxExtent().X, 0.f, RootComponent->GetComponentLocation().Z - MeshCollision_COL->GetScaledBoxExtent().Z - Z_CollisionRange };
	FVector EndLocation{ RootComponent->GetComponentLocation().X + MeshCollision_COL->GetScaledBoxExtent().X, 0.f, StartLocation.Z };
	FCollisionQueryParams TraceParams;

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
		ToggleMenuRef->SetVisibility(ESlateVisibility::Visible);
		UGameplayStatics::GetPlayerController(GetWorld(), 0)->SetInputMode(FInputModeUIOnly());
		UGameplayStatics::GetPlayerController(GetWorld(), 0)->bShowMouseCursor = true;
		UGameplayStatics::SetGamePaused(GetWorld(), true);
		ToggleMenuRef->SetFocus();
		IsToggleMenu = true;
	}
}

void ABasePawn::ToggleMenuInit()
{
	ToggleMenuRef = CreateWidget<UUserWidget>(GetWorld(), ToggleWidgetClass);
	if (ToggleMenuRef == nullptr)
		return;

	ToggleMenuRef->AddToViewport();						  // Add widget to viewport
	ToggleMenuRef->SetVisibility(ESlateVisibility::Hidden); // Set it to hidden so its not open on spawn.
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