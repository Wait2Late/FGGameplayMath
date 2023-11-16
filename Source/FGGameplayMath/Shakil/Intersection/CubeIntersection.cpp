


#include "CubeIntersection.h"


// Sets default values
ACubeIntersection::ACubeIntersection()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	StaticMeshComponent->SetStaticMesh(CubeMeshRef);
	// FTransform localTransform(FVector(1, 1, 1));
	// StaticMeshComponent->SetWorldTransform(localTransform);
	// StaticMeshComponent->SetMaterial(0, Material[0]);
}



// Called when the game starts or when spawned
void ACubeIntersection::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACubeIntersection::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

//When the SphereIntersection class intersect with this class. These methods will trigger.
void ACubeIntersection::SetMaterialCube()
{
	StaticMeshComponent->SetMaterial(0, Material[1]);
}

void ACubeIntersection::RevertMaterialCube()
{
	StaticMeshComponent->SetMaterial(0, Material[0]);
}


