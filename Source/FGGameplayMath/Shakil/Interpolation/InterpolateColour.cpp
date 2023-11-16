// Fill out your copyright notice in the Description page of Project Settings.


#include "InterpolateColour.h"

#include "Components/PointLightComponent.h"
#include "Kismet/KismetMathLibrary.h"


void AInterpolateColour::InterpolateRandomColor()
{
	FLinearColor Red = FColor::Red;    // Replace this with your desired start color
	FLinearColor Green = FColor::Green;    // Replace this with your desired end color

	//Wanted to interpolate with many different colours. But laziness got me. 
	FLinearColor LinearColor = FLinearColor::LerpUsingHSV(Red, Green, Alpha);
	
	Light->SetLightColor(LinearColor);
}


void AInterpolateColour::CountUp()
{
	if (Alpha > 1.0f)
		Alpha = 0;
	
	Alpha += 0.1f;
}

// Sets default values
AInterpolateColour::AInterpolateColour()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Light = CreateDefaultSubobject<UPointLightComponent>(TEXT("Light"));
	Light->Intensity = 1500.0f;
	RootComponent = Light;
}

// Called when the game starts or when spawned
void AInterpolateColour::BeginPlay()
{
	Super::BeginPlay();
	
	FTimerHandle TimerHandle;
	GetWorldTimerManager().SetTimer(TimerHandle, this, &AInterpolateColour::CountUp, 0.1f, true);
	Alpha = 0.0f;
}

void AInterpolateColour::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	InterpolateRandomColor();
}



