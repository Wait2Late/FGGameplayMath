// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FGGameplayMath/Demonstrator.h"
#include "FGGameplayMath/Shakil/CheckState.h"
#include "StateContext.generated.h"

UCLASS()
class FGGAMEPLAYMATH_API AStateContext : public ADemonstrator
{
	GENERATED_BODY()

	void State();
public:
	// Sets default values for this actor's properties
	AStateContext();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//Assign which area to be checked
	UPROPERTY(EditAnywhere)
	TEnumAsByte<ECheckState> CheckStateType;
};
