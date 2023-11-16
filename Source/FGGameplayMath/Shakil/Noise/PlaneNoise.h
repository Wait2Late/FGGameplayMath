// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ProceduralMeshComponent.h"
#include "GameFramework/Actor.h"
#include "PlaneNoise.generated.h"

//It creates a triangle noise
UCLASS()
class FGGAMEPLAYMATH_API APlaneNoise : public AActor
{
	GENERATED_BODY()

	TArray<FVector> Vertices;
	TArray<int32> Triangles;
	TArray<FVector2D> UVs;

	UPROPERTY()
	UProceduralMeshComponent* ProceduralMesh;

	void CreateMesh();
	
public:
	// Sets default values for this actor's properties
	APlaneNoise();

protected:
	UPROPERTY(EditAnywhere)
	UMaterialInterface* Material;
	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
