


#include "SphereIntersection.h"

#include "CubeIntersection.h"
#include "EditorMetadataOverrides.h"
#include "FGGameplayMath/Shakil/Collision/InteractCollision.h"
#include "FGGameplayMath/Shakil/StateContext/StateContext.h"


// Sets default values
ASphereIntersection::ASphereIntersection()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	StaticMeshComponent->SetStaticMesh(SphereMeshRef);
	FTransform localTransform(FVector(1, 1, 1));
	StaticMeshComponent->SetWorldTransform(localTransform);

	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("RootCollision"));

	SphereComponent->SetSphereRadius(100);
	SphereComponent->SetHiddenInGame(false);
	SphereComponent->SetupAttachment(StaticMeshComponent);

	
	SphereComponent->OnComponentBeginOverlap.AddDynamic(this, &ASphereIntersection::OnOverlapBegin);
	SphereComponent->OnComponentEndOverlap.AddDynamic(this, &ASphereIntersection::OnOverlapEnd);
}

// Called when the game starts or when spawned
void ASphereIntersection::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASphereIntersection::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

//TODO adjust this one back
void ASphereIntersection::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//I was lazy so I simply used cast. 
	ACubeIntersection* Cube = Cast<ACubeIntersection>(OtherActor);
	AInteractCollision* Interaction = Cast<AInteractCollision>(OtherActor);
	AStateContext* StateContext = Cast<AStateContext>(OtherActor);
	
	if (StateContext == OtherActor)
	{
		
		// FVector RelativeLocation = GetActorLocation() - StateContext->GetActorLocation();
		// FVector RelativeDirection = RelativeLocation.GetSafeNormal();

		// auto StateContextLocation = StateContext->GetActorLocation();
		// auto ThisLocation = GetActorLocation();

		//Think this is the one I took most inspiration from. I still do not know how to make it correctly. 
		auto State = StateContext->GetActorTransform().InverseTransformPosition(GetActorLocation());

		if (StateContext->CheckStateType.GetValue() == ECheckState::FrontAndBehind)
		{
			if (State.X > 0) GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Black, FString(TEXT("Front")));
			else if (State.X < 0) GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Black, FString(TEXT("Behind")));
		}

		if (StateContext->CheckStateType.GetValue() == ECheckState::RightAndLeft)
		{
			if (State.Y > 0) GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Black, FString(TEXT("Right")));
			else if (State.Y < 0) GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Black, FString(TEXT("Left")));
		}
		
		if (StateContext->CheckStateType.GetValue() == ECheckState::AboveAndBelow)
		{
			if (State.Z > 0) GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Black, FString(TEXT("Above")));
			else if (State.Z < 0) GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Black, FString(TEXT("Below")));
		}

		
		/*TODO Old code to remind myself why it is terrible		
		// float DotProductForward = FVector::DotProduct(RelativeDirection, StateContext->GetActorForwardVector());
		// if (DotProductForward > 0.0f && RelativeLocation.Size() <= 100.0f)
		// {
		// 	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Black, FString(TEXT("In front of StateContext")));
		// }
		//
		// float DotProductUp = FVector::DotProduct(RelativeDirection, StateContext->GetActorUpVector());
		// if (DotProductUp > 0.0f && RelativeLocation.Size() <= 100.0f)
		// {
		// 	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Black, FString(TEXT("Above StateContext")));
		// }
		// if (DotProduct > 0.0f && RelativeLocation.Size() <= 100.0f)
		// {
		// 	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Black, FString(TEXT("It works")));
		// }*/
	}

	if (Interaction == OtherActor)
	{
		switch (Interaction->InteractType.GetValue())
		{
			case EInteractiveType::Invisibility: Interaction->MakeInvisible();break;
			case EInteractiveType::BigScale: Interaction->MakeScaleLarge(); break;
			case EInteractiveType::Destroy: Interaction->DestroyActor(); break;
		}
	}
	
	if (Cube == OtherActor)
	{
		Cube->SetMaterialCube();
	}
	// else
	// {
	// 	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Black, FString(TEXT("It works")));
	// }
	
}


void ASphereIntersection::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	ACubeIntersection* Cube = Cast<ACubeIntersection>(OtherActor);
	AInteractCollision* Interaction = Cast<AInteractCollision>(OtherActor);
	
	if (Interaction == OtherActor)
	{
		switch (Interaction->InteractType.GetValue())
		{
			case EInteractiveType::Invisibility: Interaction->RevertInvisible();
			case EInteractiveType::BigScale: Interaction->RevertScale(); break;
		}
	} 


	
	if (Cube == OtherActor)
	{
		Cube->RevertMaterialCube();
	}
}


