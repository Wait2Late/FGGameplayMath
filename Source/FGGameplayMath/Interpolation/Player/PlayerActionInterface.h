// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "PlayerActionInterface.generated.h"

UINTERFACE()
class UPlayerActionInterface : public UInterface
{
	GENERATED_BODY()
};

class FGGAMEPLAYMATH_API IPlayerActionInterface
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void Move(const FVector2D Vector);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void Look(const FVector2D Vector);
};