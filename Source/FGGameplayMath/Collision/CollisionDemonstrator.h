// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SphereComponent.h"
#include "FGGameplayMath/Demonstrator.h"
#include "CollisionDemonstrator.generated.h"

UENUM(Blueprintable)
enum ECollisionType
{
	PlaneCollider,
	SphereCollider
};

UCLASS(BlueprintType, Blueprintable)
class FGGAMEPLAYMATH_API ACollisionDemonstrator
	: public ADemonstrator
{
	GENERATED_BODY()

	UPROPERTY()
	USphereComponent* SphereComponent;

protected:
	virtual void BeginPlay() override;

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TEnumAsByte<ECollisionType> CollisionType;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float Mass;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float MoveSpeed;	
	
	ACollisionDemonstrator();
	virtual void Tick(float DeltaTime) override;
	virtual bool ShouldTickIfViewportsOnly() const override;

	void AddForce(const FVector& Force);
	void Step(const float DeltaTime);

	float GetRadius() const;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	bool ApplyGravity;

	UPROPERTY()
	FVector Acceleration;

	UPROPERTY()
	FVector Velocity;
};
