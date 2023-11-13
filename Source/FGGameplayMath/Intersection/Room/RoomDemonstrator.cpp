// Fill out your copyright notice in the Description page of Project Settings.
#include "RoomDemonstrator.h"

#include "RoomManager.h"
#include "FGGameplayMath/Intersection/IntersectionUtility.h"

void ARoomDemonstrator::BeginPlay()
{
	Super::BeginPlay();

	const auto RoomManager = GetWorld()->GetSubsystem<URoomManager>();
	RoomManager->RegisterRoom(this);
}

ARoomDemonstrator::ARoomDemonstrator()
{}

bool ARoomDemonstrator::IsInsideRoom(const FVector& Location) const
{
	return UIntersectionUtility::PointAABB(
		Location,
		GetActorLocation() + Min,
		GetActorLocation() + Max
		);
}

void ARoomDemonstrator::AddToPopulation(AStateDemonstrator* Demonstrator)
{
	if(!RoomPopulation.Contains(Demonstrator))
		RoomPopulation.Add(Demonstrator);
}

void ARoomDemonstrator::RemoveFromPopulation(AStateDemonstrator* Demonstrator)
{
	if(RoomPopulation.Contains(Demonstrator))
		RoomPopulation.Remove(Demonstrator);
}