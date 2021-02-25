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

	// Create objects and link them
	BoxCollision_COL = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Collision"));
	RootComponent = BoxCollision_COL;

	BoxMesh_SM = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Box Mesh"));
	BoxMesh_SM->AttachToComponent(RootComponent, FAttachmentTransformRules::SnapToTargetIncludingScale);
}

// Called when the game starts or when spawned
void ABaseBox::BeginPlay()
{
	Super::BeginPlay();

	// Cast Red and Blue Player
	RedPawnActorRef = UGameplayStatics::GetActorOfClass(GetWorld(), ARedPawn::StaticClass());
	BluePawnActorRef = UGameplayStatics::GetActorOfClass(GetWorld(), ABluePawn::StaticClass());

	// Dynamic (OnHit)
	BoxCollision_COL->OnComponentBeginOverlap.AddDynamic(this, &ABaseBox::OnOverlap);
}

void ABaseBox::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool FromSweep, const FHitResult& Hit)
{
	DestroyActor(OtherActor);
}

void ABaseBox::DestroyActor(AActor* OtherActor)
{
	if (OtherActor == nullptr)
		UE_LOG(LogTemp, Error, TEXT("Error, Actor doesn't exist!"));
}

