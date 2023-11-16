// Fill out your copyright notice in the Description page of Project Settings.


#include "PlaneNoise.h"


void APlaneNoise::CreateMesh()
{
	//It makes a square
	Vertices.Add(FVector(-50, 0,  50));
	Vertices.Add(FVector(-50, 0, -50));
	Vertices.Add(FVector( 50, 0,  50));
	Vertices.Add(FVector( 50, 0, -50));

	UVs.Add(FVector2D(0, 0));
	UVs.Add(FVector2D(0, 1));
	UVs.Add(FVector2D(1, 0));
	UVs.Add(FVector2D(1, 1));

	//Then makes a Triangle shape
	Triangles.Add(0);
	Triangles.Add(1);
	Triangles.Add(2);
	
	ProceduralMesh->CreateMeshSection(0, Vertices, Triangles, TArray<FVector>(), UVs, TArray<FColor>(), TArray<FProcMeshTangent>(), true);
	if (Material)
	{
		ProceduralMesh->SetMaterial(0, Material);
	}
}

// Sets default values
APlaneNoise::APlaneNoise()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	ProceduralMesh = CreateDefaultSubobject<UProceduralMeshComponent>("ProceduralMesh");
	RootComponent = ProceduralMesh;
}

// Called when the game starts or when spawned
void APlaneNoise::BeginPlay()
{
	Super::BeginPlay();

	CreateMesh();
}

// Called every frame
void APlaneNoise::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

