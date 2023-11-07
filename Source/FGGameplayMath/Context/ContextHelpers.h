// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#define TEST_BIT(Bitmask, Bit) (((Bitmask) & (1 << static_cast<int32>(Bit))) > 0)
#define TEST_BITS(Bitmask, Bit) (((Bitmask) & Bit) == Bit)
#define SET_BIT(Bitmask, Bit) (Bitmask |= 1 << static_cast<int32>(Bit))
#define CLEAR_BIT(Bitmask, Bit) (Bitmask &= ~(1 << static_cast<int32>(Bit)))

#include "CoreMinimal.h"
#include "RelativeContext.h"
#include "FGGameplayMath/Constants.h"
#include "FGGameplayMath/State/StateDemonstrator.h"
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
	static int32 GetRelativeContext(const AActor* Target, const AActor* Other)
	{
		int32 ReturnContext = 0;

		const auto TargetLocation = Target->GetActorLocation();
		const auto OtherLocation = Other->GetActorLocation();
		const auto Direction = OtherLocation - TargetLocation;

		const auto LocalSpaceLocation = Target->GetActorTransform().InverseTransformPosition(OtherLocation);

		if(LocalSpaceLocation.X > 0)
			SET_BIT(ReturnContext, ERelativeContext::InFront);
		else if(LocalSpaceLocation.X < 0)
			SET_BIT(ReturnContext, ERelativeContext::Behind);

		if(LocalSpaceLocation.Y > 0)
			SET_BIT(ReturnContext, ERelativeContext::ToTheRight);
		else if(LocalSpaceLocation.Y < 0)
			SET_BIT(ReturnContext, ERelativeContext::ToTheLeft);
		
		if(LocalSpaceLocation.Z > 0)
			SET_BIT(ReturnContext, ERelativeContext::Above);
		else if(LocalSpaceLocation.Z < 0)
			SET_BIT(ReturnContext, ERelativeContext::Below);
		
		const auto Distance = Direction.Length();
		if(Distance > CONST_Range)
			SET_BIT(ReturnContext, ERelativeContext::Far);
		else
			SET_BIT(ReturnContext, ERelativeContext::Close);
		
		const auto Angle = FindAngle(Target->GetActorForwardVector(), Direction.GetSafeNormal());
		const auto HalfGlobalAngle = CONST_Angle * .5f;
		if(Angle < HalfGlobalAngle && Angle > -HalfGlobalAngle)
			SET_BIT(ReturnContext, ERelativeContext::Seen);
		else
			SET_BIT(ReturnContext, ERelativeContext::Unseen);

		const auto FacingDot = FVector::DotProduct(Target->GetActorForwardVector(), Other->GetActorForwardVector());
		if(FacingDot > CONST_DirectionThreshold)
			SET_BIT(ReturnContext, ERelativeContext::FacingSame);
		else if(FacingDot < -CONST_DirectionThreshold)
			SET_BIT(ReturnContext, ERelativeContext::FacingOpposite);

		if(const auto OtherStateDemonstrator = Cast<AStateDemonstrator>(Other))
		{
			const auto Health = OtherStateDemonstrator->Health;
			
			if(Health < CONST_DyingThreshold)
				SET_BIT(ReturnContext, ERelativeContext::NearDeath);
			else if (Health < CONST_HurtThreshold)
				SET_BIT(ReturnContext, ERelativeContext::Hurt);
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
	static bool ContextPredicate(const int32 Test, const int32 Value)
    {
		return TEST_BITS(Test, Value);
    }	
};