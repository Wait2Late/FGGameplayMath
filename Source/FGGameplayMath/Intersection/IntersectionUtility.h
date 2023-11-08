// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "IntersectionUtility.generated.h"

/**
 * 
 */
UCLASS()
class FGGAMEPLAYMATH_API UIntersectionUtility : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	// SphereSphereIntersection
	UFUNCTION(BlueprintCallable, Category = "Intersection")
	static bool SphereSphere(
		const FVector CenterA,
		const float RadiusA,
		const FVector CenterB,
		const float RadiusB)
	{
		const auto Diff = CenterA - CenterB;
		const auto RadiusSum = RadiusA + RadiusB;
		return Diff.Dot(Diff) <= RadiusSum * RadiusSum;
	}

	// LineSphereIntersection
	UFUNCTION(BlueprintCallable, Category = "Intersection")
	static bool RaySphere(
		const FVector Origin,
		const FVector Direction,
		const FVector Center,
		const float Radius)
	{
		const auto W = Center - Origin;
		const auto WSQ = W.Dot(W);
		const auto Projection = W.Dot(Direction);
		const auto RSQ = Radius * Radius;

		// If sphere is behind ray, no intersection
		if(Projection < 0.f && WSQ > RSQ)
			return false;

		const auto VSQ = Direction.Dot(Direction);

		// Diff vs radius
		return (VSQ * WSQ - Projection * Projection <= VSQ * Radius * Radius);
	}

	// AABB-AABB Intersection
	UFUNCTION(BlueprintCallable, Category = "Intersection")
	static bool AABBIntersect(
		const FVector MinA,
		const FVector MaxA,
		const FVector MinB,
		const FVector MaxB)
	{
		if(MinA.X > MaxB.X || MinB.X > MaxA.X)
			return false;

		if(MinA.Y > MaxB.Y || MinB.Y > MaxA.Y)
			return false;

		if(MinA.Z > MaxB.Z || MinB.Z > MaxA.Z)
			return false;

		return true;
	}

	// SphereAABB
	UFUNCTION(BlueprintCallable, Category = "Intersection")
	static bool SphereAABB(
		const FVector Origin,
		const float Radius,
		const FVector Min,
		const FVector Max)
	{
		auto SquareDistance = 0.f;

		if(Origin.X < Min.X)
			SquareDistance += (Min.X - Origin.X) * (Min.X - Origin.X);

		if(Origin.X > Max.X)
			SquareDistance += (Origin.X - Max.X) * (Origin.X - Max.X);

		if(Origin.Y < Min.Y)
			SquareDistance += (Min.Y - Origin.Y) * (Min.Y - Origin.Y);

		if(Origin.Y > Max.Y)
			SquareDistance += (Origin.Y - Max.Y) * (Origin.Y - Max.Y);

		if(Origin.Z < Min.Z)
			SquareDistance += (Min.Z - Origin.Z) * (Min.Z - Origin.Z);

		if(Origin.Z > Max.Z)
			SquareDistance += (Origin.Z - Max.Z) * (Origin.Z - Max.Z);

		return SquareDistance <= Radius * Radius;
	}	

	// LinePlaneIntersection
	UFUNCTION(BlueprintCallable, Category = "Intersection")
	static bool RayPlane(
		const FVector Origin,
		const FVector Direction,
		const FVector PlaneNormal,
		const FVector PlaneOrigin,
		FVector& ContactPoint)
	{
		const auto CoordDot = PlaneNormal.Dot(PlaneOrigin);
		const auto DirectionDot = PlaneNormal.Dot(Direction);

		// Skip if plane normal and ray share direction.
		if(DirectionDot >= 0)
		{
			return false;
		}

		const auto T = (CoordDot - PlaneNormal.Dot(Origin)) / DirectionDot;
		ContactPoint = Origin + Direction.GetSafeNormal() * T;
		
		return true;
	}

	UFUNCTION(BlueprintCallable, Category = "Intersection")
	static bool RayTriangle(
		const FVector Origin,
		const FVector Direction,
		const FVector V0,
		const FVector V1,
		const FVector V2,
		FVector& ContactPoint)
	{
		const FVector E1 = V1 - V0;
		const FVector E2 = V2 - V0; 

		const auto P = Direction.Cross(E2);
		const auto A = E1.Dot(P);

		// No intersection or infinite intersections
		if(FMath::IsNearlyEqual(A, 0.f))
			return false;

		const auto F = 1.f / A;
		const auto S = Origin - V0;
		const auto U = F * S.Dot(P);

		// Outside triangle bounds on U axis.
		if(U < 0.f || U > 1.f)
			return false;

		const auto Q = S.Cross(E1);
		const auto V = F * Direction.Dot(Q);

		// Outside triangle bounds V axis (remove 'U +' to check quad instead of triangle).
		if(V < 0.f || U + V > 1.f)
			return false;

		const auto T = F * E2.Dot(Q);

		ContactPoint = Origin + (Direction * T);
		
		return T >= 0.f;
	}
};