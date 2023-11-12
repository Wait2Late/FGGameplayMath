// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CollisionDemonstrator.h"
#include "Subsystems/WorldSubsystem.h"
#include "CollisionSubsystem.generated.h"

/**
 * 
 */
UCLASS()
class FGGAMEPLAYMATH_API UCollisionSubsystem
	: public UTickableWorldSubsystem
{
	GENERATED_BODY()

	UPROPERTY()
	TArray<ACollisionDemonstrator*> CollisionDemonstrators;

public:
	virtual void Tick(float DeltaTime) override;

	void RegisterDemonstrator(ACollisionDemonstrator* Demonstrator);
	void UnregisterDemonstrator(ACollisionDemonstrator* Demonstrator);

	virtual TStatId GetStatId() const override;
};
