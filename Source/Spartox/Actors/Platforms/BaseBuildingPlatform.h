// Puzzle platformer game done by Vladimir Mokanj - 15.02.2021

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseBuildingPlatform.generated.h"

UCLASS()
class SPARTOX_API ABaseBuildingPlatform : public AActor
{
	GENERATED_BODY()

public:
	// Constructor
	ABaseBuildingPlatform();

	// Variables
	UPROPERTY(Category = "Components", BlueprintReadOnly, VisibleAnywhere)
		USceneComponent* RootSceneComponent;

protected:
	// Functions
	virtual void PlatformConfig(FString* PlatformClassLocation, UStaticMeshComponent* &BasePlatform_Mesh, UStaticMesh* &Platform_Asset);

private:
	// Variables
	int32 LOCAL_RandomRotateRange{ 0 };
	FVector LOCAL_BoxExtend{ 42.5f, 42.5f, 40.f };
	float LOCAL_PlatformSize{ 0.f };
	float LOCAL_PlatformLength{ 0.f };

	// Functions
	UFUNCTION(BlueprintCallable)
		void DynamicPlatformCreation(UPARAM(ref) bool& _isVertical, UPARAM(ref) bool& _isRotateEnabled, UPARAM(ref) uint8& _PlatformNumber, UPARAM(ref) float& _PlatformScale, UClass* _PlatformType);
};
