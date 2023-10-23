// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FGGameplayMath/Context/RelativeContext.h"
#include "Math/BoxSphereBounds.h"
#include "GameFramework/Actor.h"
#include "StateDemonstrator.generated.h"

UCLASS(hidecategories=(Input, Movement, Collision, Rendering, HLOD, WorldPartition, DataLayers, Replication, Physics, Networking, Actor, LevelInstance, Cooking))
class FGGAMEPLAYMATH_API AStateDemonstrator : public AActor
{
	GENERATED_BODY()

	float Time;

	FBoxSphereBounds3f AABB;

	ERelativeContext GetRelativeContext(const FTransform* Self, const FTransform* Other);
	bool ContextPredicate(const ERelativeContext Test, const ERelativeContext Value);
	float FindAngle(const FVector SelfForward, const FVector TargetForward);
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Sets default values for this actor's properties
	AStateDemonstrator();
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Meta = (Bitmask, BitmaskEnum = "ERelativeContext"))
	uint8 ContextFlags;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FVector Extents;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(UIMin=0,UIMax=10))
	float Duration;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FRuntimeFloatCurve Curve;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(UIMin=0,UIMax=100))
	float Health;
};