// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ProceduralMeshComponent.h"
#include "NoiseTerrainCopy.generated.h"


//Not using these. Just need the inspiration because I could not fetch it from repository
UCLASS()
class FGGAMEPLAYMATH_API ANoiseTerrainCopy : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ANoiseTerrainCopy();
	
private:
	UPROPERTY(EditAnywhere)
	UProceduralMeshComponent* ProceduralMeshComponent;

	TArray<float> NoiseArray;

	TArray<FVector> Vertices;
	TArray<FVector> Normals;
	TArray<FVector2D> UV;
	TArray<FColor> Colors;
	TArray<int32> Triangles;
	TArray<FProcMeshTangent> Tangents;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FVector ProcMeshScale = FVector(18.75f, 18.75f, 0.5f);

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector2D Offset;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Resolution = 64;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Scale = 0.05f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Strength = 1.f;

	UPROPERTY(EditAnywhere)
	UMaterialInterface* Material;

	virtual void BeginPlay() override;

	void GenerateNoiseMap();

	void GenerateMesh();

	void CalculateNormals();

public:	
	virtual void OnConstruction(const FTransform& Transform) override;
	virtual void Tick(float DeltaTime) override;
};
