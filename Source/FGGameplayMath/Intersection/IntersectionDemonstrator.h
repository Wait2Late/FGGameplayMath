// Fill out your copyright notice in the Description page of Project Settings.
#pragma once

#include "CoreMinimal.h"
#include "FGGameplayMath/Demonstrator.h"
#include "CollisionShape.h"
#include "Intersection.h"
#include "IntersectionDemonstrator.generated.h"

UCLASS()
class FGGAMEPLAYMATH_API AIntersectionDemonstrator
	: public ADemonstrator
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TEnumAsByte<EIntersection> IntersectionType;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Sphere")
	float Radius;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="AABB", meta = (MakeEditWidget = true))
	FVector Min;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="AABB", meta = (MakeEditWidget = true))
	FVector Max;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Triangle", meta = (MakeEditWidget = true))
	FVector V0;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Triangle", meta = (MakeEditWidget = true))
	FVector V1;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Triangle", meta = (MakeEditWidget = true))
	FVector V2;	

	UPROPERTY()
	bool Drawn;
	
	AIntersectionDemonstrator();
	void DrawShape(const FColor Color);
};