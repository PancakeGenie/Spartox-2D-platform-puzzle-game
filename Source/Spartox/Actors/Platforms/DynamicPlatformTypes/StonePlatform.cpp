// Puzzle platformer game done by Vladimir Mokanj - 15.02.2021

#include "StonePlatform.h"

AStonePlatform::AStonePlatform()
{
	// Create all objects and link them
	// ---------------------------------
	// Responsible for mesh creation
	Platform_Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Stone Mesh"));
	Platform_Mesh->SetupAttachment(RootComponent);

	// Parent holds the platform config, didn't want to create config for each future platform.
	PlatformConfig(&MeshLocation, Platform_Mesh, Platform_Asset);
}
