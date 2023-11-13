// Fill out your copyright notice in the Description page of Project Settings.
#include "RoomPopulationComponent.h"

URoomPopulationComponent::URoomPopulationComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void URoomPopulationComponent::BeginPlay()
{
	Super::BeginPlay();
	RoomManager = GetWorld()->GetSubsystem<URoomManager>();
}

void URoomPopulationComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                             FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	CurrentRoom = RoomManager->GetClosestRoom(GetOwner()->GetActorLocation());

	if(CurrentRoom)
	{
		DrawDebugString(
			GetWorld(),
			GetOwner()->GetActorLocation(),
			CurrentRoom->GetName(),
			GetOwner(),
			FColor::Red,
			0.f
			);		
	}
}