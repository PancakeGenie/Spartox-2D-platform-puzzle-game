// Puzzle platformer game done by Vladimir Mokanj - 15.02.2021


#include "BaseBuildingPlatform.h"
#include "Kismet/KismetMathLibrary.h"
#include "Components/SceneComponent.h"
#include "../../Global_Log.h"
#include "Components/BoxComponent.h"

DEFINE_LOG_CATEGORY_STATIC(BaseBuildingPlatformLog, All, All)

// Sets default values
ABaseBuildingPlatform::ABaseBuildingPlatform()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	// Create all objects and link them
	// ---------------------------------
	// Root component of BaseBuildingPlatform
	RootSceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootScene"));
	RootComponent = RootSceneComponent;
}

// ------------------------------------------------------------------------------------------------------------------------------
// Configuration used by child actors. Whatever you want child actor to do, set it in here.
// ------------------------------------------------------------------------------------------------------------------------------
void ABaseBuildingPlatform::PlatformConfig(FString* PlatformClassLocation, UStaticMeshComponent* &Platform_Mesh, UStaticMesh* &Platform_Asset)
{
	// Reflection
	ConstructorHelpers::FObjectFinder<UStaticMesh> Platform_BP(**PlatformClassLocation);
	if (Platform_BP.Object != nullptr)
	{
		Platform_Asset = Platform_BP.Object;

		// Assign mesh to component
		Platform_Mesh->SetStaticMesh(Platform_Asset);
		Platform_Mesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		Platform_Mesh->SetCastShadow(false);
	}
}
// ------------------------------------------------------------------------------------------------------------------------------

// ------------------------------------------------------------------------------------------------------------------------------
// Function that creates platforms during runtime.
// ------------------------------------------------------------------------------------------------------------------------------
void ABaseBuildingPlatform::DynamicPlatformCreation(UPARAM(ref) bool& _isVertical, UPARAM(ref) bool& _isRotateEnabled, UPARAM(ref) uint8& _PlatformNumber, UPARAM(ref) float& _PlatformScale, UClass* _PlatformType)
{
	// Checker
	if (this->RootComponent == nullptr)
		return;

	// PlatformSize depends on if it's vertical or horizontal platform placement
	_isVertical ? LOCAL_PlatformSize = 2 * _PlatformScale * LOCAL_BoxExtend.Z
			    : LOCAL_PlatformSize = 2 * _PlatformScale * LOCAL_BoxExtend.X;

	LOCAL_PlatformLength = _PlatformNumber * LOCAL_PlatformSize;

	// Used to randomize Yaw rotation of each platform
	if (_isRotateEnabled == true)
		LOCAL_RandomRotateRange = 3;
	else
		LOCAL_RandomRotateRange = 0;

	// Number of platforms to be created
	for (uint8 i = 0; i < _PlatformNumber; ++i)
	{
		UChildActorComponent* Child = NewObject<UChildActorComponent>(this, UChildActorComponent::StaticClass(), *("Platform_" + FString::FromInt(i)));				// Dynamically create new object
		if (Child != nullptr)
		{
			Child->CreationMethod = EComponentCreationMethod::UserConstructionScript;																				// Creation method - makes sure that child doesn't get deleted when construction script is re-reun
			Child->AttachToComponent(this->RootComponent, FAttachmentTransformRules::KeepRelativeTransform);														// Attach it to a component but keep transfrom relative to it's origin
			Child->SetChildActorClass(_PlatformType);

			// Relative world position (Rotation, Scale, Location)
			Child->SetRelativeRotation(FRotator{ 0.f, FMath::RandRange(0, LOCAL_RandomRotateRange) * 90.f, 0.f });
			Child->SetRelativeScale3D(FVector{ _PlatformScale });

			// Location depends if it's vertical positioning or horizontal platform placement
			_isVertical ? Child->SetRelativeLocation(FVector{ 0.f, 0.f, LOCAL_PlatformSize * i })
						: Child->SetRelativeLocation(FVector{ LOCAL_PlatformSize * -i, 0.f, 0.f });
		}
	}

	// Create collision box
	UBoxComponent* PlatformCollision_COL = NewObject<UBoxComponent>(this, GetFName());
	if (PlatformCollision_COL != nullptr)
	{
		PlatformCollision_COL->CreationMethod = EComponentCreationMethod::UserConstructionScript;
		PlatformCollision_COL->AttachTo(this->RootComponent);
		PlatformCollision_COL->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
		PlatformCollision_COL->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);

		// Relative world position (Scale, Location and BoxExtention)
		PlatformCollision_COL->SetRelativeScale3D(FVector{ _PlatformScale });

		// Location and BoxExtention depends if it's vertical or horizontal platform placement
		_isVertical ? (PlatformCollision_COL->SetRelativeLocation(FVector{ 0.f, 0.f, (LOCAL_PlatformLength - LOCAL_PlatformSize) / 2 }),
					   PlatformCollision_COL->SetBoxExtent(FVector{ LOCAL_BoxExtend.X, LOCAL_BoxExtend.Y, LOCAL_BoxExtend.Z * _PlatformNumber }))	   // Change Collision box extention to match the length of the platform
				    : (PlatformCollision_COL->SetRelativeLocation(FVector{ ((LOCAL_PlatformLength - LOCAL_PlatformSize) / 2) * -1, 0.f, 0.f }),
					   PlatformCollision_COL->SetBoxExtent(FVector{ LOCAL_BoxExtend.X * _PlatformNumber, LOCAL_BoxExtend.Y, LOCAL_BoxExtend.Z }));
	}

	RegisterAllComponents();																														   // Registers all components so that they don't dissapear in the world
}
// ------------------------------------------------------------------------------------------------------------------------------