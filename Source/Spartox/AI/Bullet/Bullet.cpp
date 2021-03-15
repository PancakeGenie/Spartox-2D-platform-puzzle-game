// Puzzle platformer game done by Vladimir Mokanj - 15.02.2021

#include "Bullet.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"
#include "../../Pawns/Player/BluePawn.h"
#include "../../Pawns/Player/RedPawn.h"
#include "../../GameMode/Spartox_GameModeGameplay.h"
#include "GameFramework/ProjectileMovementComponent.h"

// Sets default values
ABullet::ABullet()
{
	// Create all objects and link them
	// ---------------------------------
	RootSceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root Component"));
	RootComponent = RootSceneComponent;

	// Responsible for collision detection (destroy self)
	BulletDestroyCollision_COL = CreateDefaultSubobject<UBoxComponent>(TEXT("Bullet Destruction Collision"));
	BulletDestroyCollision_COL->AttachToComponent(RootComponent, FAttachmentTransformRules::SnapToTargetIncludingScale);

	// Responsible for collision detection (allow walking if red)
	BulletWalkOnCollision_COL = CreateDefaultSubobject<UBoxComponent>(TEXT("Bullet Walk On Collision"));
	BulletWalkOnCollision_COL->AttachToComponent(RootComponent, FAttachmentTransformRules::SnapToTargetIncludingScale);

	// Visible mesh to player
	BulletMesh_SM = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Bullet Mesh"));
	BulletMesh_SM->AttachToComponent(RootComponent, FAttachmentTransformRules::SnapToTargetIncludingScale);

	// Used for bullet movement
	BulletMovement_CPT = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Bullet Movement"));
}

void ABullet::BeginPlay()
{
	Super::BeginPlay();

	// Cast players and GameMode
	RedPawn = Cast<ARedPawn>(UGameplayStatics::GetActorOfClass(GetWorld(), ARedPawn::StaticClass()));
	BluePawn = Cast<ABluePawn>(UGameplayStatics::GetActorOfClass(GetWorld(), ABluePawn::StaticClass()));
	GameModeRef = Cast<ASpartox_GameModeGameplay>(UGameplayStatics::GetGameMode(this));

	// Dynamic (OnHit) delegate
	BulletDestroyCollision_COL->OnComponentBeginOverlap.AddDynamic(this, &ABullet::OnOverlap);
}

// ------------------------------------------------------------------------------------------------------------------------------
// Actor interaction on overlap -------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------------------------------------
void ABullet::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool FromSweep, const FHitResult& Hit)
{
	if (OtherActor == RedPawn)
	{
		Destroy();
		return;
	}

	if (OtherActor == BluePawn)
		GameModeRef->ResetCurrentLevel();
}
// ------------------------------------------------------------------------------------------------------------------------------
