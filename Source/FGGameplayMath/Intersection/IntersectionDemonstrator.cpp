// Fill out your copyright notice in the Description page of Project Settings.
#include "IntersectionDemonstrator.h"

#include "IntersectionSubsystem.h"
#include "ShapeDrawUtility.h"

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

// This is a whole bunch of sloppy bookkeeping that should be separated into multiple classes. 
void AIntersectionDemonstrator::DrawShape(const FColor Color)
{
	if(Drawn) return;
	
	Drawn = true;

	const auto Location = GetActorLocation();
	const auto WorldContext = GetWorld();
// <<<<<<< Updated upstream
// =======
//
// 	const auto C = FVector(Min.X, Max.Y, Min.Z);
// 	const auto F = FVector(Min.X, Max.Y, Max.Z);
// 	const auto A = FVector(Min.X, Min.Y, Max.Z);
// 	const auto D = FVector(Max.X, Min.Y, Max.Z);
// 	const auto E = FVector(Max.X, Min.Y, Min.Z);
// 	const auto B = FVector(Max.X, Max.Y, Min.Z);
//
// 	const FVector TransformedV0 = GetActorTransform().TransformPosition(V0);
// 	const FVector TransformedV1 = GetActorTransform().TransformPosition(V1);
// 	const FVector TransformedV2 = GetActorTransform().TransformPosition(V2);
// 	
// 	const auto PlaneExtents = FVector(
// 		1000.f,
// 		1000.f,
// 		0.f
// 		);	
// >>>>>>> Stashed changes
	
	switch(IntersectionType.GetValue())
	{
	case EIntersection::Sphere:
		UShapeDrawUtility::Sphere(WorldContext, Location, Radius, Color);
		break;

	case EIntersection::Plane:
		UShapeDrawUtility::Plane(WorldContext, Location, GetActorUpVector(), GetActorQuat(), Color);
		break;
	
	case EIntersection::AABB:
		UShapeDrawUtility::Box(WorldContext, Location, Min, Max, Color);
		break;

	case EIntersection::Triangle:
		UShapeDrawUtility::Triangle(WorldContext, GetActorTransform(), V0, V1, V2, Color);
		break;

	case EIntersection::Ray:
		UShapeDrawUtility::Ray(WorldContext, GetActorLocation(), GetActorForwardVector(), Color);
		break;		
	}
}