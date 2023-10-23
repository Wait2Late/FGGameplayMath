// Fill out your copyright notice in the Description page of Project Settings.
#include "StateDemonstrator.h"
#include "FGGameplayMath/Constants.h"
#include "DrawDebugHelpers.h"

// Sets default values
AStateDemonstrator::AStateDemonstrator()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	const auto Location = GetActorTransform().GetLocation();
	AABB.Origin.Set(Location.X, Location.Y, Location.Z);
	
	Time = 0.f;
}

ERelativeContext AStateDemonstrator::GetRelativeContext(const FTransform* Self, const FTransform* Other)
{
	ERelativeContext ReturnContext = {};

	const auto SelfPosition = Self->GetLocation();
	const auto OtherPosition = Other->GetLocation();

	if (FVector::Distance(SelfPosition, OtherPosition) > Range)
		return ERelativeContext::None;

	const auto LocalPosition = Self->InverseTransformPosition(OtherPosition);

	if (LocalPosition.Y > 0)
		ReturnContext |= ERelativeContext::ToTheRight;
	else if(LocalPosition.Y < 0)
		ReturnContext |= ERelativeContext::ToTheLeft;
        
	if (LocalPosition.Z > 0)
		ReturnContext |= ERelativeContext::Above;
	else if(LocalPosition.Z < 0)
		ReturnContext |= ERelativeContext::Below;
        
	if (LocalPosition.X > 0)
		ReturnContext |= ERelativeContext::InFront;
	else if(LocalPosition.X < 0)
		ReturnContext |= ERelativeContext::Behind;

	auto Direction = (OtherPosition - SelfPosition);
	Direction.Normalize();
	
	auto AngleToTarget = FindAngle(Self->GetRotation().GetForwardVector(), Direction);
	auto HalfGlobalAngle = Angle * .5f;
	if (AngleToTarget < HalfGlobalAngle && AngleToTarget > -HalfGlobalAngle)
		ReturnContext |= ERelativeContext::Seen;
        
	return ReturnContext;
}

bool AStateDemonstrator::ContextPredicate(const ERelativeContext Test, const ERelativeContext Value)
{
	return (Value & Test) == Test;
}

float AStateDemonstrator::FindAngle(const FVector SelfForward, const FVector TargetForward)
{
	auto dot = FVector::DotProduct(SelfForward, TargetForward);
	dot = FMath::Clamp(dot, -1.f, 1.f);
	return FMath::RadiansToDegrees(FMath::Acos(dot));
}

// Called when the game starts or when spawned
void AStateDemonstrator::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AStateDemonstrator::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	AABB.BoxExtent.Set(Extents.X, Extents.Y, Extents.Z);

	DrawDebugBox(GetWorld(), static_cast<FVector>(AABB.Origin), static_cast<FVector>(AABB.BoxExtent), FColor::Blue);

	Time += DeltaTime;

	float Value = 0.f;
	const float T = Time / Duration;

	if(Curve.ExternalCurve)
	{
		Value = Curve.ExternalCurve->FloatCurve.Eval(T);
	}
	else
	{
		Value = Curve.EditorCurveData.Eval(T);
	}

	GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Green, FString::SanitizeFloat(Value));
}