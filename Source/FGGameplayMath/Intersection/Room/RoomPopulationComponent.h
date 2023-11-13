// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "RoomDemonstrator.h"
#include "RoomManager.h"
#include "Components/ActorComponent.h"
#include "RoomPopulationComponent.generated.h"

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class FGGAMEPLAYMATH_API URoomPopulationComponent : public UActorComponent
{
	GENERATED_BODY()

	UPROPERTY()
	ARoomDemonstrator* CurrentRoom;

	UPROPERTY()
	URoomManager* RoomManager;
	
protected:
	virtual void BeginPlay() override;

public:
	URoomPopulationComponent();
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;

	bool IsCurrentlyInARoom() const
	{
		return CurrentRoom != nullptr;
	}
};