// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FGGameplayMath/Demonstrator.h"
#include "InteractCollision.generated.h"

UENUM(Blueprintable)
enum EInteractiveType
{
	Invisibility,
	BigScale,
	Destroy
};

UCLASS()
class FGGAMEPLAYMATH_API AInteractCollision : public ADemonstrator
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AInteractCollision();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	
	UPROPERTY(EditAnywhere)
	TEnumAsByte<EInteractiveType> InteractType;

	void MakeInvisible();
	void RevertInvisible();

	void MakeScaleLarge();
	void RevertScale();

	void DestroyActor();
	
};
