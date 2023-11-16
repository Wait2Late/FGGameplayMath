#pragma once

#include "CoreMinimal.h"
#include "Components/SphereComponent.h"
#include "FGGameplayMath/Demonstrator.h"
#include "Components/PrimitiveComponent.h"
#include "SphereIntersection.generated.h"


//I use this one to check collision on many of the maps. Should have named it differently, But it was too late.
UCLASS()
class FGGAMEPLAYMATH_API ASphereIntersection : public ADemonstrator
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ASphereIntersection();
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

		
	UPROPERTY(Blueprintable)
	USphereComponent* SphereComponent;

	UPROPERTY(EditAnywhere)
	UStaticMesh* SphereMeshRef;


	UFUNCTION()
	void OnOverlapBegin(
		UPrimitiveComponent* OverlappedComp,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult
		);

	UFUNCTION()
	void OnOverlapEnd(
		UPrimitiveComponent* OverlappedComp,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex);
	
};
