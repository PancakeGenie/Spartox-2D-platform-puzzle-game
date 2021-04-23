// Puzzle platformer game done by Vladimir Mokanj - 15.02.2021

#pragma once

#include "CoreMinimal.h"
#include "../BaseBuildingPlatform.h"
#include "DirtPlatform.generated.h"

UCLASS()
class SPARTOX_API ADirtPlatform : public ABaseBuildingPlatform
{
	GENERATED_BODY()
	
public:
	// Constructor
	ADirtPlatform();

private:
	// Variables
	FString MeshLocation{ "StaticMesh'/Game/Assets/Actors/Platforms/DirtPlatform.DirtPlatform'" };
	UStaticMeshComponent* Platform_Mesh;
	UStaticMesh* Platform_Asset;
};
