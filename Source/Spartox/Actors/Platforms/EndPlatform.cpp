// Puzzle platformer game done by Vladimir Mokanj - 15.02.2021

#include "EndPlatform.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"
#include "../Collectables/KeyItem.h"
#include "../../GameMode/Spartox_GameModeBase.h"

AEndPlatform::AEndPlatform()
{
	// Create all objects and link them
	// ---------------------------------
	// Responsible for collision detection
	EndLevelCollision_COL = CreateDefaultSubobject<UBoxComponent>(TEXT("End level Collision"));
	EndLevelCollision_COL->AttachToComponent(RootComponent, FAttachmentTransformRules::SnapToTargetIncludingScale);
}

void AEndPlatform::BeginPlay()
{
	GameModeRef = Cast<ASpartox_GameModeBase>(UGameplayStatics::GetGameMode(this));

	// Dynamic (OnOverlap) delegate
	EndLevelCollision_COL->OnComponentBeginOverlap.AddDynamic(this, &AEndPlatform::OnOverlap);
}

// ------------------------------------------------------------------------------------------------------------------------------
// Trigger on overlap functions -------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------------------------------------
void AEndPlatform::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool FromSweep, const FHitResult& Hit)
{
	AActor* PawnActorRef = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);

	if (OtherActor == PawnActorRef)
	{
		AActor* Keys = UGameplayStatics::GetActorOfClass(GetWorld(), AKeyItem::StaticClass());

		// Check if key is picked up, if it is, go to the next level (this will be completely done tomorrow)
		if (Keys == nullptr)
			GameModeRef->NextLevel();
	}
}
// ------------------------------------------------------------------------------------------------------------------------------