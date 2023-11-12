// Fill out your copyright notice in the Description page of Project Settings.
#include "StateDemonstrator.h"
#include "DrawDebugHelpers.h"
#include "FGGameplayMath/Constants.h"

// Sets default values
AStateDemonstrator::AStateDemonstrator()
{
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;
}

// Called every frame
void AStateDemonstrator::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	const FVector Cross = FVector::CrossProduct(GetActorForwardVector(), GetActorRightVector());

	DrawDebugLine(GetWorld(), GetActorLocation(), GetActorLocation() + GetActorForwardVector() * 100.f, FColor::Red);
	DrawDebugLine(GetWorld(), GetActorLocation(), GetActorLocation() + GetActorRightVector() * 100.f, FColor::Green);
	DrawDebugLine(GetWorld(), GetActorLocation(), GetActorLocation() + Cross * 100.f, FColor::Blue);
	
	if(!DrawArc)
		return;
	
	DrawDebugCone(
		GetWorld(),
		GetActorLocation(),
		GetActorForwardVector(),
		GContextRange,
		FMath::DegreesToRadians(GContextAngle * .5f),
		0.f,
		1,
		FColor::Green
		);
}

bool AStateDemonstrator::ShouldTickIfViewportsOnly() const
{
	return true;
}