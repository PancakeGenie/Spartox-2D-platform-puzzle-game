// Puzzle platformer game done by Vladimir Mokanj - 15.02.2021


#include "BasePawn.h"
#include "Components/BoxComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "../../GameMode/Spartox_GameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "PawnSkills.h"

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

	SpringArm_SA = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
	SpringArm_SA->AttachToComponent(RootComponent, FAttachmentTransformRules::SnapToTargetIncludingScale);

	PlayerCamera_CAM = CreateDefaultSubobject<UCameraComponent>(TEXT("Player Camera"));
	PlayerCamera_CAM->AttachToComponent(SpringArm_SA, FAttachmentTransformRules::SnapToTargetIncludingScale);

	PawnSkillsRef = CreateDefaultSubobject<UPawnSkills>(TEXT("Action Component"));

	// Default values
	isPlayerAlive = true;
	canJump = true;
}

void ABasePawn::BeginPlay()
{
	// Assign game mode ref to GameModeRef handle
	GameModeRef = Cast<ASpartox_GameModeBase>(UGameplayStatics::GetGameMode(this));

	// Dynamic (OnHit)
	MeshCollision_COL->OnComponentHit.AddDynamic(this, &ABasePawn::OnHit);
}

// ------------------------------------------------------------------------------------------------------------------------------
// Player movement and jump -----------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------------------------------------
void ABasePawn::SetupPlayerInputComponent(UInputComponent* PlayerInput)
{
	Super::SetupPlayerInputComponent(PlayerInput);

	// Link movement and jump
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
		// Movement is based on frame rate (DeltaSeconds), scale value (Movement direction) and MovementSpeed (Arbitrary value)
		FVector vCalcMovement{ GetWorld()->GetDeltaSeconds() * ScaleValue * fMovementSpeed, 0.f, 0.f };

		// Move player
		AddActorWorldOffset(vCalcMovement);
	}
}

void ABasePawn::Jump()
{
	if (isPlayerAlive == true && canJump == true && isJumping == false)
	{
		// Jump is based on fJumpForce
		FVector vCalcJump{ 0.f, 0.f, fJumpForce };

		// Jump, ignore player mass
		MeshCollision_COL->AddImpulse(vCalcJump, NAME_None, true);

		// Player is jumping now
		isJumping = true;
	}
}

void ABasePawn::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if (isJumping == true)
	{
		//UE_LOG(LogTemp, Warning, TEXT("Impulse: %f"), Hit.ImpactNormal.Z);
		isJumping = false;
	}
}
// ------------------------------------------------------------------------------------------------------------------------------

// ------------------------------------------------------------------------------------------------------------------------------
// Player switch ----------------------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------------------------------------
void ABasePawn::SwitchPlayer()
{
	if (isPlayerAlive == true)
		GameModeRef->SwitchPlayer();
}

// ------------------------------------------------------------------------------------------------------------------------------

void ABasePawn::SetIsPlayerAlive(bool setIsPlayerAlive)
{
	isPlayerAlive = setIsPlayerAlive;
}