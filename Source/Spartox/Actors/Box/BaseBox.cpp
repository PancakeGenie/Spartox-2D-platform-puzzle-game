// Puzzle platformer game done by Vladimir Mokanj - 15.02.2021

#include "BaseBox.h"
#include "../../Pawns/Player/RedPawn.h"
#include "../../Pawns/Player/BluePawn.h"
#include "Kismet/GameplayStatics.h"
#include "Components/BoxComponent.h"

// Sets default values
ABaseBox::ABaseBox()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	// Create all objects and link them
	// ---------------------------------
	// Responsible for collision detection
	BoxCollision_COL = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Collision"));
	RootComponent = BoxCollision_COL;

	// Visible mesh to player
	BoxMesh_SM = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Box Mesh"));
	BoxMesh_SM->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void ABaseBox::BeginPlay()
{
	Super::BeginPlay();

	// Dynamic (OnHit) delegate
	BoxCollision_COL->OnComponentBeginOverlap.AddDynamic(this, &ABaseBox::OnOverlap);
}

// ------------------------------------------------------------------------------------------------------------------------------
// Actor interaction on hit -----------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------------------------------------
void ABaseBox::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool FromSweep, const FHitResult& Hit)
{
	DestroyActor(OtherActor);
}

void ABaseBox::DestroyActor(AActor* OtherActor)
{
	if (OtherActor == nullptr)
		UE_LOG(LogTemp, Error, TEXT("Error, Actor doesn't exist!"));
}
// ------------------------------------------------------------------------------------------------------------------------------
