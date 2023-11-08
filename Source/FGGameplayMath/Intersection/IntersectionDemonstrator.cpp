// Fill out your copyright notice in the Description page of Project Settings.
#include "IntersectionDemonstrator.h"

#include "IntersectionSubsystem.h"

AIntersectionDemonstrator::AIntersectionDemonstrator()
{
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;
}

void AIntersectionDemonstrator::BeginPlay()
{
	Super::BeginPlay();

	const auto SubSystem = GetWorld()->GetSubsystem<UIntersectionSubsystem>();
	SubSystem->RegisterDemonstrator(this);
}

void AIntersectionDemonstrator::DrawShape(const FColor Color)
{
	if(Drawn) return;
	
	Drawn = true;

	// This is a whole bunch of sloppy book keeping that should be separated into multiple classes. 
	const auto Location = GetActorLocation();
	const auto WorldContext = GetWorld();

	const auto A = FVector(Min.X, Min.Y, Max.Z);
	const auto B = FVector(Max.X, Max.Y, Min.Z);
	const auto C = FVector(Min.X, Max.Y, Min.Z);
	const auto D = FVector(Max.X, Min.Y, Max.Z);
	const auto E = FVector(Max.X, Min.Y, Min.Z);
	const auto F = FVector(Min.X, Max.Y, Max.Z);

	const FVector TransformedV0 = GetActorTransform().TransformPosition(V0);
	const FVector TransformedV1 = GetActorTransform().TransformPosition(V1);
	const FVector TransformedV2 = GetActorTransform().TransformPosition(V2);
	
	const auto PlaneExtents = FVector(
		1000.f,
		1000.f,
		0.f
		);	
	
	switch(IntersectionType.GetValue())
	{
	case EIntersection::Sphere:
		DrawDebugSphere(
			WorldContext,
			Location,
			Radius,
			16,
			Color
			);
		break;

	case EIntersection::Plane:
		DrawDebugPoint(
			WorldContext,
			Location,
			25.f,
			Color
			);

		DrawDebugLine(
			WorldContext,
			Location,
			Location + (GetActorUpVector() * 100.f),
			Color
			);
		
		DrawDebugBox(
			WorldContext,
			Location,
			PlaneExtents,
			GetActorQuat(),
			Color
			);
		break;

	case EIntersection::AABB:
		DrawDebugPoint(
			WorldContext,
			Location + Min,
			25.f,
			Color
			);

		DrawDebugPoint(
			WorldContext,
			Location + Max,
			25.f,
			Color
			);
		
		DrawDebugLine(
			WorldContext,
			Location + Max,
			Location + B,
			Color
			);
		
		DrawDebugLine(
			WorldContext,
			Location + Min,
			Location + A,
			Color
			);

		DrawDebugLine(
			WorldContext,
			Location + Min,
			Location + C,
			Color
			);

		DrawDebugLine(
			WorldContext,
			Location + C,
			Location + F,
			Color
			);

		DrawDebugLine(
			WorldContext,
			Location + C,
			Location + B,
			Color
			);

		DrawDebugLine(
			WorldContext,
			Location + Max,
			Location + F,
			Color
			);

		DrawDebugLine(
			WorldContext,
			Location + Max,
			Location + D,
			Color
			);

		DrawDebugLine(
			WorldContext,
			Location + D,
			Location + A,
			Color
			);
		
		DrawDebugLine(
			WorldContext,
			Location + A,
			Location + F,
			Color
			);

		DrawDebugLine(
			WorldContext,
			Location + D,
			Location + E,
			Color
			);

		DrawDebugLine(
			WorldContext,
			Location + B,
			Location + E,
			Color
			);

		DrawDebugLine(
			WorldContext,
			Location + Min,
			Location + E,
			Color
			);				
		break;

	case EIntersection::Triangle:
		DrawDebugPoint(
			WorldContext,
			TransformedV0,
			25.f,
			Color);

		DrawDebugPoint(
			WorldContext,
			TransformedV1,
			25.f,
			Color);

		DrawDebugPoint(
			WorldContext,
			TransformedV2,
			25.f,
			Color);		
		
		DrawDebugLine(
			WorldContext,
			TransformedV0,
			TransformedV1,
			Color
			);

		DrawDebugLine(
			WorldContext,
			TransformedV1,
			TransformedV2,
			Color
			);

		DrawDebugLine(
			WorldContext,
			TransformedV2,
			TransformedV0,
			Color
			);
		break;

	case EIntersection::Ray:
		DrawDebugLine(
			WorldContext,
			Location,
			Location + (GetActorForwardVector() * 1000.f),
			Color
			);
		break;		
	}
}
