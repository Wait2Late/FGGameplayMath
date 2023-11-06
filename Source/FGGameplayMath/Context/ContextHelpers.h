// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "RelativeContext.h"
#include "FGGameplayMath/Constants.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "ContextHelpers.generated.h"

/**
 * 
 */
UCLASS()
class FGGAMEPLAYMATH_API UContextHelpers : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "Context")
	static int32 GetRelativeContext(const AActor* Target, const AActor* Other, FString &ContextString)
	{
		ContextString = "Context > "; 
		int32 ReturnContext = 0;

		const auto TargetLocation = Target->GetActorLocation();
		const auto OtherLocation = Other->GetActorLocation();
		const auto Direction = OtherLocation - TargetLocation;

		const auto LocalSpaceLocation = Target->GetActorTransform().InverseTransformPosition(OtherLocation);

		if(LocalSpaceLocation.X > 0)
		{
			ReturnContext |= static_cast<int32>(ERelativeContext::InFront);
			ContextString += ":InFront"; 
		}
		else if(LocalSpaceLocation.X < 0)
		{
			ReturnContext |= static_cast<int32>(ERelativeContext::Behind);
			ContextString += ":Behind";
		}

		if(LocalSpaceLocation.Y > 0)
		{
			ReturnContext |= static_cast<int32>(ERelativeContext::ToTheRight);
			ContextString += ":ToTheRight"; 
		}
		else if(LocalSpaceLocation.Y < 0)
		{
			ReturnContext |= static_cast<int32>(ERelativeContext::ToTheLeft);
			ContextString += ":ToTheLeft";
		}
		
		if(LocalSpaceLocation.Z > 0)
		{
			ReturnContext |= static_cast<int32>(ERelativeContext::Above);
			ContextString += ":Above";
		}
		else if(LocalSpaceLocation.Z < 0)
		{
			ReturnContext |= static_cast<int32>(ERelativeContext::Below);
			ContextString += ":Below";
		}
		
		const auto Distance = Direction.Length();
		if(Distance > CONST_Range)
		{
			ReturnContext |= static_cast<int32>(ERelativeContext::Far);
			ContextString += ":Far";
		}
		else
		{
			ReturnContext |= static_cast<int32>(ERelativeContext::Close);
			ContextString += ":Close";
		}
		
		const auto Angle = FindAngle(Target->GetActorForwardVector(), Direction.GetSafeNormal());
		const auto HalfGlobalAngle = CONST_Angle * .5f;
		if(Angle < HalfGlobalAngle && Angle > -HalfGlobalAngle)
		{
			ReturnContext |= static_cast<int32>(ERelativeContext::Seen);
			ContextString += ":Seen";
		}
		else
		{
			ReturnContext |= static_cast<int32>(ERelativeContext::Unseen);
			ContextString += ":Unseen";
		}

		const auto FacingDot = FVector::DotProduct(Target->GetActorForwardVector(), Other->GetActorForwardVector());
		if(FacingDot > .9f)
		{
			ReturnContext |= static_cast<int32>(ERelativeContext::FacingSame);
			ContextString += ":FacingSame";
		}
		else if(FacingDot < -.9f)
		{
			ReturnContext |= static_cast<int32>(ERelativeContext::FacingOpposite);
			ContextString += ":FacingOpposite";
		}

		return ReturnContext;
	}

	UFUNCTION(BlueprintCallable, Category = "Context")
	static float FindAngle(const FVector SelfForward, const FVector TargetForward)
	{
		auto Dot = FVector::DotProduct(SelfForward, TargetForward);
		Dot = FMath::Clamp(Dot, -1.f, 1.f);
		return FMath::RadiansToDegrees(FMath::Acos(Dot));
	}

	UFUNCTION(BlueprintCallable, Category = "Context")
	static bool ContextPredicate(
		UPARAM(meta=(Bitmask, BitmaskEnum = "ERelativeContext")) int32 Test,
		UPARAM(meta=(Bitmask, BitmaskEnum = "ERelativeContext")) int32 Value)
    {
        return (Value & Test);
    }	
};