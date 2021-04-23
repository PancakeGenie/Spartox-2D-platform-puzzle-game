// Puzzle platformer game done by Vladimir Mokanj - 15.02.2021

#pragma once

#include "CoreMinimal.h"
#include "../BaseBuildingPlatform.h"
#include "SandPlatform.generated.h"

UCLASS()
class SPARTOX_API ASandPlatform : public ABaseBuildingPlatform
{
	GENERATED_BODY()
	
public:
	// Constructor
	ASandPlatform();

private:
	// Variables
	FString MeshLocation{ "StaticMesh'/Game/Assets/Actors/Platforms/SandPlatform.SandPlatform'" };
	UStaticMeshComponent* Platform_Mesh;
	UStaticMesh* Platform_Asset;
};
