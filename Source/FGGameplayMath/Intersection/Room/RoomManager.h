// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "RoomDemonstrator.h"
#include "Subsystems/WorldSubsystem.h"
#include "RoomManager.generated.h"

/**
 * 
 */
UCLASS()
class FGGAMEPLAYMATH_API URoomManager : public UWorldSubsystem
{
	GENERATED_BODY()

	UPROPERTY()
	TArray<ARoomDemonstrator*> Rooms;

public:
	UFUNCTION()
	void RegisterRoom(ARoomDemonstrator* Room);

	UFUNCTION()
	ARoomDemonstrator* GetClosestRoom(const FVector& Location);
};