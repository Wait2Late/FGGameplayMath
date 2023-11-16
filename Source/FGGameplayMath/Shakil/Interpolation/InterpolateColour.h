// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FGGameplayMath/Demonstrator.h"
#include "Components/PointLightComponent.h"
#include "InterpolateColour.generated.h"

UCLASS()
class FGGAMEPLAYMATH_API AInterpolateColour : public ADemonstrator
{
	GENERATED_BODY()

	void InterpolateRandomColor();

	void CountUp();
public:
	// Sets default values for this actor's properties
	AInterpolateColour();
	

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaSeconds) override;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UPointLightComponent* Light;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float Alpha = 0.0f;
};
