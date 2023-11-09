// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "IntersectionDemonstrator.h"
#include "Subsystems/WorldSubsystem.h"
#include "IntersectionSubsystem.generated.h"

/**
 * 
 */
UCLASS()
class FGGAMEPLAYMATH_API UIntersectionSubsystem
	: public UTickableWorldSubsystem
{
private:
	GENERATED_BODY()

	TArray<AIntersectionDemonstrator*> IntersectionDemonstrators;

	UPROPERTY()
	APlayerController* PlayerControllerInstance;
	
public:
	virtual bool IsTickableInEditor() const override;
	virtual void Tick(float DeltaTime) override;

	void RegisterPlayerController(APlayerController* PlayerController);
	
	void RegisterDemonstrator(AIntersectionDemonstrator* Demonstrator);
	void UnregisterDemonstrator(AIntersectionDemonstrator* Demonstrator);

	virtual TStatId GetStatId() const override;
};