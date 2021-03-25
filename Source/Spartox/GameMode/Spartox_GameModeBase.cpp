// Puzzle platformer game done by Vladimir Mokanj - 15.02.2021

#include "Spartox_GameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "../Global_Log.h"
#include "Spartox_GameInstance.h"

DEFINE_LOG_CATEGORY_STATIC(GameModeBaseLog, All, All)

ASpartox_GameModeBase::ASpartox_GameModeBase()
{
	DefaultPawnClass = nullptr;
}

void ASpartox_GameModeBase::BeginPlay()
{
	Super::BeginPlay();

	GameInstanceRef = Cast<USpartox_GameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	if (GameInstanceRef == nullptr)
		LOG(GameModeBaseLog, "GameInstanceRef failed to cast!");
}