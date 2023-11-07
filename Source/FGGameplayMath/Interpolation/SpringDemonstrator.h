// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FGGameplayMath/Demonstrator.h"
#include "Kismet/KismetMathLibrary.h"
#include "SpringDemonstrator.generated.h"

UCLASS()
class FGGAMEPLAYMATH_API ASpringDemonstrator
	: public ADemonstrator
{
	GENERATED_BODY()

	FVector Origin;
	FVector Goal;

protected:
	virtual void BeginPlay() override;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (MakeEditWidget = true))
	FVector TargetPosition;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FVectorSpringState SpringState;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float Stiffness = .5f;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float Damping = .5f;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float Mass = 1.f;

public:
	ASpringDemonstrator();
	virtual void Tick(float DeltaTime) override;
};
