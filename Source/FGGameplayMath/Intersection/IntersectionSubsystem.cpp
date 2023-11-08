// Fill out your copyright notice in the Description page of Project Settings.
#include "IntersectionSubsystem.h"

#include "IntersectionUtility.h"

bool UIntersectionSubsystem::IsTickableInEditor() const
{
	return true;
}

void UIntersectionSubsystem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if(IntersectionDemonstrators.Num() == 1)
	{
		IntersectionDemonstrators[0]->DrawShape(FColor::Green);
		return;
	}	

	for(const auto Demonstrator : IntersectionDemonstrators)
	{
		Demonstrator->Drawn = false;
	}

	for(const auto DemonstratorA : IntersectionDemonstrators)
	{
		for(const auto DemonstratorB : IntersectionDemonstrators)
		{
			if(DemonstratorA == DemonstratorB)
				continue;

			auto IntersectionTest = false;

			if(DemonstratorA->IntersectionType == EIntersection::Sphere &&
				DemonstratorB->IntersectionType == EIntersection::Sphere)
			{
				IntersectionTest = UIntersectionUtility::SphereSphere(
					DemonstratorA->GetActorLocation(),
					DemonstratorA->Radius,
					DemonstratorB->GetActorLocation(),
					DemonstratorB->Radius
				);
			}

			if(DemonstratorA->IntersectionType == EIntersection::Ray &&
				DemonstratorB->IntersectionType == EIntersection::Sphere && !IntersectionTest)
			{
				IntersectionTest = UIntersectionUtility::RaySphere(
					DemonstratorA->GetActorLocation(),
					DemonstratorA->GetActorForwardVector(),
					DemonstratorB->GetActorLocation(),
					DemonstratorB->Radius
					);
			}

			if(DemonstratorA->IntersectionType == EIntersection::Ray && 
				DemonstratorB->IntersectionType == EIntersection::Plane && !IntersectionTest)
			{
				FVector ContactPoint;
				
				IntersectionTest = UIntersectionUtility::RayPlane(
					DemonstratorA->GetActorLocation(),
					DemonstratorA->GetActorForwardVector(),
					DemonstratorB->GetActorUpVector(),
					DemonstratorB->GetActorLocation(),
					ContactPoint
					);

				if(IntersectionTest)
				{
					DrawDebugPoint(
						GetWorld(),
						ContactPoint,
						25.f,
						FColor::Cyan
						);					
				}
			}

			if(DemonstratorA->IntersectionType == EIntersection::Ray && 
				DemonstratorB->IntersectionType == EIntersection::Triangle && !IntersectionTest)
			{
				FVector ContactPoint;
				
				IntersectionTest = UIntersectionUtility::RayTriangle(
					DemonstratorA->GetActorLocation(),
					DemonstratorA->GetActorForwardVector(),
					DemonstratorB->GetActorTransform().TransformPosition(DemonstratorB->V0),
					DemonstratorB->GetActorTransform().TransformPosition(DemonstratorB->V1),
					DemonstratorB->GetActorTransform().TransformPosition(DemonstratorB->V2),
					ContactPoint
					);

				if(IntersectionTest)
				{
					DrawDebugPoint(
						GetWorld(),
						ContactPoint,
						25.f,
						FColor::Cyan
						);					
				}
			}

			if(DemonstratorA->IntersectionType == EIntersection::Sphere &&
				DemonstratorB->IntersectionType == EIntersection::AABB && !IntersectionTest)
			{
				IntersectionTest = UIntersectionUtility::SphereAABB(
					DemonstratorA->GetActorLocation(),
					DemonstratorA->Radius,
					DemonstratorB->GetActorLocation() + DemonstratorB->Min,
					DemonstratorB->GetActorLocation() + DemonstratorB->Max
					);
			}			

			if(DemonstratorA->IntersectionType == EIntersection::AABB &&
				DemonstratorB->IntersectionType == EIntersection::AABB && !IntersectionTest)
			{
				IntersectionTest = UIntersectionUtility::AABBIntersect(
					DemonstratorA->GetActorLocation() + DemonstratorA->Min,
					DemonstratorA->GetActorLocation() + DemonstratorA->Max,
					DemonstratorB->GetActorLocation() + DemonstratorB->Min,
					DemonstratorB->GetActorLocation() + DemonstratorB->Max
					);
			}
			
			if(IntersectionTest)
			{
				DemonstratorA->DrawShape(FColor::Red);
				DemonstratorB->DrawShape(FColor::Red);
			}
		}
	}

	for(const auto Demonstrator : IntersectionDemonstrators)
	{
		if(!Demonstrator->Drawn)
			Demonstrator->DrawShape(FColor::Green);
	}	
}

void UIntersectionSubsystem::RegisterDemonstrator(AIntersectionDemonstrator* Demonstrator)
{
	if(!IntersectionDemonstrators.Contains(Demonstrator))
		IntersectionDemonstrators.Add(Demonstrator);
}

void UIntersectionSubsystem::UnregisterDemonstrator(AIntersectionDemonstrator* Demonstrator)
{
	if(IntersectionDemonstrators.Contains(Demonstrator))
		IntersectionDemonstrators.Remove(Demonstrator);
}

TStatId UIntersectionSubsystem::GetStatId() const
{
	return GetStatID();
}