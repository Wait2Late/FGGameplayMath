// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FGGameplayMath/Intersection/IntersectionDemonstrator.h"
#include "FGGameplayMath/State/StateDemonstrator.h"
#include "RoomDemonstrator.generated.h"

UCLASS()
class FGGAMEPLAYMATH_API ARoomDemonstrator
	: public AIntersectionDemonstrator
{
	GENERATED_BODY()

	UPROPERTY()
	TArray<AStateDemonstrator*> RoomPopulation;

protected:
	virtual void BeginPlay() override;
	
public:
	ARoomDemonstrator();

	bool IsInsideRoom(const FVector& Location) const;
	
	void AddToPopulation(AStateDemonstrator* Demonstrator);
	void RemoveFromPopulation(AStateDemonstrator* Demonstrator);
};