// Fill out your copyright notice in the Description page of Project Settings.
#include "SpringDemonstrator.h"

#include "Kismet/KismetMathLibrary.h"

ASpringDemonstrator::ASpringDemonstrator()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ASpringDemonstrator::BeginPlay()
{
	Super::BeginPlay();
	Origin = GetActorLocation();
}

void ASpringDemonstrator::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	Goal = Origin + TargetPosition;

	const auto MoveVector = UKismetMathLibrary::VectorSpringInterp(
		GetActorLocation(),
		Goal,
		SpringState,
		Stiffness,
		Damping,
		DeltaTime,
		Mass
		);

	SetActorLocation(MoveVector);
}