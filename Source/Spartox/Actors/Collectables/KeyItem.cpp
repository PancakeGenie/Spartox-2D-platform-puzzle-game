// Puzzle platformer game done by Vladimir Mokanj - 15.02.2021

#include "KeyItem.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AKeyItem::AKeyItem()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Create objects and link them
	KeyCollision_COL = CreateDefaultSubobject<UBoxComponent>(TEXT("Key Collision"));
	RootComponent = KeyCollision_COL;

	KeyMesh_SM = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Key Mesh"));
	KeyMesh_SM->AttachToComponent(RootComponent, FAttachmentTransformRules::SnapToTargetIncludingScale);
}

void AKeyItem::BeginPlay()
{
	Super::BeginPlay();

	// Dynamic (OnHit)
	KeyCollision_COL->OnComponentBeginOverlap.AddDynamic(this, &AKeyItem::OnOverlap);
}

// Called every frame
void AKeyItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	RotateKey();
}

void AKeyItem::RotateKey()
{
	FRotator rSetKeyRotation{ KeyMesh_SM->GetComponentRotation().Pitch, KeyMesh_SM->GetComponentRotation().Yaw - fRotationSpeed, KeyMesh_SM->GetComponentRotation().Roll };

	// Rotate the key by fixed value
	KeyMesh_SM->SetWorldRotation(rSetKeyRotation);
}

void AKeyItem::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool FromSweep, const FHitResult& Hit)
{
	AActor* PlayerRef = UGameplayStatics::GetPlayerPawn(this, 0);

	// Check if other actor is the reason for collision
	if (OtherActor == PlayerRef)
		Destroy();
}
