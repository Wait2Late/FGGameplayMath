// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PlayerActionInterface.h"
#include "GameFramework/Pawn.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "FGGameplayMath/Interpolation/Interpolator.h"
#include "InterpPlayer.generated.h"

UCLASS()
class FGGAMEPLAYMATH_API AInterpPlayer : public APawn,
	public IPlayerActionInterface
{
	GENERATED_BODY()

	float CurrentLookRotation;

	FVector MoveVector;

protected:
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FInterpolator AccelerationInterpolator;
	
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	UCameraComponent* CameraComponent;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	UCapsuleComponent* CapsuleComponent;

public:
	AInterpPlayer();

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float MoveSpeed = 1000.f;

	void Look(const FVector2D Vector); virtual void Look_Implementation(const FVector2D Vector) override;
	void Move(const FVector2D Vector); virtual void Move_Implementation(const FVector2D Vector) override;
};