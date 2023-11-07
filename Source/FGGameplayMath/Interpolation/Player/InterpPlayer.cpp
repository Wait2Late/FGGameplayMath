// Fill out your copyright notice in the Description page of Project Settings.
#include "InterpPlayer.h"
#include "Kismet/KismetMathLibrary.h"

AInterpPlayer::AInterpPlayer()
{
	PrimaryActorTick.bCanEverTick = true;

	CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleCollider"));
	CapsuleComponent->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	CapsuleComponent->SetCollisionObjectType(ECC_Pawn);
	CapsuleComponent->SetCollisionResponseToChannel(ECC_WorldStatic, ECR_Block);
	CapsuleComponent->InitCapsuleSize(55.f, 96.f);
	CapsuleComponent->SetSimulatePhysics(true);

	// Hacky way to stop the capsule from inheriting collision rotation.
	constexpr float InertiaTensorScale = 10000.f;
	CapsuleComponent->BodyInstance.InertiaTensorScale = FVector(InertiaTensorScale, InertiaTensorScale, InertiaTensorScale);

	SetRootComponent(CapsuleComponent);

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	CameraComponent->SetupAttachment(CapsuleComponent);
	CameraComponent->SetRelativeLocation(FVector(0,0,100.f));
}

void AInterpPlayer::BeginPlay()
{
	Super::BeginPlay();
	AccelerationInterpolator.Initialize();
}

void AInterpPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	AccelerationInterpolator.Update(DeltaTime);

	auto TransformedVector = UKismetMathLibrary::TransformDirection(
		GetActorTransform(),
		MoveVector
	);

	TransformedVector *= MoveSpeed * AccelerationInterpolator.GetValue();

	SetActorLocation(
		GetActorLocation() + 
		TransformedVector * DeltaTime
	);
}

void AInterpPlayer::Look_Implementation(const FVector2D Vector)
{
	// Rotate directly on the horizontal axis
	AddActorLocalRotation(
		FRotator(
			0.f, 
			Vector.X, 
			0.f)
	);

	// Clamp vertical axis
	CurrentLookRotation += Vector.Y;
	CurrentLookRotation = FMath::ClampAngle(
		CurrentLookRotation,
		-90.f,
		90.f
	);

	CameraComponent->SetWorldRotation(
		FRotator(
			CurrentLookRotation, 
			GetActorRotation().Yaw, 
			0.f)
	);
}

void AInterpPlayer::Move_Implementation(const FVector2D Vector)
{
	MoveVector.X = Vector.Y;
	MoveVector.Y = -Vector.X;
	MoveVector.Z = 0.f;

	if(MoveVector.Length() == 0.f)
	{
		AccelerationInterpolator.Reset();
	}
}