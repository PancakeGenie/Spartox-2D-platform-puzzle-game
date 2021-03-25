// Puzzle platformer game done by Vladimir Mokanj - 15.02.2021

#include "StaticTurret.h"
#include "Components/BoxComponent.h"
#include "Components/ArrowComponent.h"
#include "TimerManager.h"
#include "Bullet/Bullet.h"

#include "../Global_Log.h"

DEFINE_LOG_CATEGORY_STATIC(StaticTurretLog, All, All)

// Sets default values
AStaticTurret::AStaticTurret()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	// Create all objects and link them
	// ---------------------------------
	// Responsible for collision detection (destroy self)
	CannonCollision_COL = CreateDefaultSubobject<UBoxComponent>(TEXT("Cannon Collision"));
	RootComponent = CannonCollision_COL;

	// Visible mesh to player
	CannonBaseMesh_SM = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Cannon Base Mesh"));
	CannonBaseMesh_SM->AttachToComponent(RootComponent, FAttachmentTransformRules::SnapToTargetIncludingScale);

	CannonMesh_SM = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Cannon Mesh"));
	CannonMesh_SM->AttachToComponent(CannonBaseMesh_SM, FAttachmentTransformRules::SnapToTargetIncludingScale);

	// Used for bullet spawn location/rotation
	BulletArrow_ARW = CreateDefaultSubobject<UArrowComponent>(TEXT("Bullet Arrow Spawn Location"));
	BulletArrow_ARW->AttachToComponent(CannonMesh_SM, FAttachmentTransformRules::SnapToTargetIncludingScale);

	// Cast blueprint (reflection)
	static ConstructorHelpers::FObjectFinder<UBlueprint> Bullet_BP(TEXT("Blueprint'/Game/Blueprints/AI/Bullet/Bullet_BP.Bullet_BP'"));
	if (Bullet_BP.Object != nullptr)
		Bullet = (UClass*)Bullet_BP.Object->GeneratedClass;
}

// Called when the game starts or when spawned
void AStaticTurret::BeginPlay()
{
	Super::BeginPlay();

	// Repeatable time manager
	GetWorldTimerManager().SetTimer(BulletSpawnTimer, this, &AStaticTurret::SpawnBullet, BulletSpawnDelay, true, 0.0f);
}

void AStaticTurret::SpawnBullet()
{
	const FVector SpawnLocation{ BulletArrow_ARW->GetComponentLocation() };
	const FRotator SpawnRotation{ BulletArrow_ARW->GetComponentRotation() };
	FActorSpawnParameters SpawnInfo;

	GetWorld()->SpawnActor(Bullet, &SpawnLocation, &SpawnRotation, SpawnInfo);
}