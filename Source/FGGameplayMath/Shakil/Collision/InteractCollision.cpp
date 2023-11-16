// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractCollision.h"


// Sets default values
AInteractCollision::AInteractCollision()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AInteractCollision::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AInteractCollision::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

//Here it checks to collide and makes few 
void AInteractCollision::MakeInvisible()
{
	StaticMeshComponent->SetHiddenInGame(true);
}

void AInteractCollision::RevertInvisible()
{
	StaticMeshComponent->SetHiddenInGame(false);
}

void AInteractCollision::MakeScaleLarge()
{
	FVector NewVector = FVector(0.2f,0.2f,0.2f);
	StaticMeshComponent->SetWorldScale3D(NewVector);
}

void AInteractCollision::RevertScale()
{
	FVector NewVector = FVector(0.2f,0.2f,0.2f);
	NewVector /= 2;
	StaticMeshComponent->SetWorldScale3D(NewVector);
}

void AInteractCollision::DestroyActor()
{
	Destroy();

}



