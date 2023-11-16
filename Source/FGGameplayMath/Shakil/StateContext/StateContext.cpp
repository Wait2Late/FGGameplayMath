// Fill out your copyright notice in the Description page of Project Settings.


#include "StateContext.h"




// Sets default values
AStateContext::AStateContext()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AStateContext::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AStateContext::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	const FVector Cross = FVector::CrossProduct(GetActorForwardVector(), GetActorRightVector());

	DrawDebugLine(GetWorld(), GetActorLocation(), GetActorLocation() + GetActorForwardVector() * 200.f, FColor::Red);
	DrawDebugLine(GetWorld(), GetActorLocation(), GetActorLocation() + GetActorRightVector() * 200.f, FColor::Green);
	DrawDebugLine(GetWorld(), GetActorLocation(), GetActorLocation() + Cross * 200.f, FColor::Blue);

	
}

void AStateContext::State()
{
	
}