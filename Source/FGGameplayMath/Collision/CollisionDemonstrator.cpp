// Fill out your copyright notice in the Description page of Project Settings.
#include "CollisionDemonstrator.h"

#include "CollisionSubsystem.h"
#include "FGGameplayMath/Intersection/ShapeDrawUtility.h"
#include "Kismet/KismetMathLibrary.h"

ACollisionDemonstrator::ACollisionDemonstrator()
{
	PrimaryActorTick.bCanEverTick = true;
	SphereComponent = CreateDefaultSubobject<USphereComponent>("SphereComponent");
	StaticMeshComponent->SetupAttachment(SphereComponent);
	SetRootComponent(SphereComponent);
}

void ACollisionDemonstrator::BeginPlay()
{
	Super::BeginPlay();
	const auto Subsystem = GetWorld()->GetSubsystem<UCollisionSubsystem>();
	Subsystem->RegisterDemonstrator(this);

	Acceleration = UKismetMathLibrary::RandomUnitVector() * MoveSpeed;
}

void ACollisionDemonstrator::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if(CollisionType == ECollisionType::SphereCollider)
	{
		UShapeDrawUtility::Sphere(
			GetWorld(),
			GetActorLocation(),
			SphereComponent->GetScaledSphereRadius(),
			FColor::Orange
			);		
	}
	else
	{
		UShapeDrawUtility::Plane(
			GetWorld(),
			GetActorLocation(),
			GetActorUpVector(),
			GetActorQuat(),
			FColor::Orange
			);
	}
}

bool ACollisionDemonstrator::ShouldTickIfViewportsOnly() const
{
	return true;
}

void ACollisionDemonstrator::AddForce(const FVector& Force)
{
	Acceleration += Force;
}

void ACollisionDemonstrator::Step(const float DeltaTime)
{
	Velocity += Acceleration;
	const auto Location = GetActorLocation();
	SetActorLocation(Location + Velocity * DeltaTime);
	Acceleration = FVector::ZeroVector;	
}

float ACollisionDemonstrator::GetRadius() const
{
	return SphereComponent->GetScaledSphereRadius();
}