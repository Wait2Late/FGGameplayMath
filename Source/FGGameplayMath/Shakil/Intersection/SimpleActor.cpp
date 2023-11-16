// Fill out your copyright notice in the Description page of Project Settings.


#include "SimpleActor.h"


// Sets default values
ASimpleActor::ASimpleActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
}

// Called when the game starts or when spawned
void ASimpleActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASimpleActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

