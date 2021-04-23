// Puzzle platformer game done by Vladimir Mokanj - 15.02.2021

#pragma once

#include "CoreMinimal.h"
#include "../BaseBuildingPlatform.h"
#include "StonePlatform.generated.h"

UCLASS()
class SPARTOX_API AStonePlatform : public ABaseBuildingPlatform
{
	GENERATED_BODY()
	
public:
	// Constructor
	AStonePlatform();

private:
	// Variables
	FString MeshLocation{ "StaticMesh'/Game/Assets/Actors/Platforms/StonePlatform.StonePlatform'" };
	UStaticMeshComponent* Platform_Mesh;
	UStaticMesh* Platform_Asset;
};