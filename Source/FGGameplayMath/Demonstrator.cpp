// Fill out your copyright notice in the Description page of Project Settings.
#include "Demonstrator.h"

ADemonstrator::ADemonstrator()
{
	PrimaryActorTick.bCanEverTick = true;
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
}