#pragma once

#include "CoreMinimal.h"
#include "FGGameplayMath/Demonstrator.h"
#include "CubeIntersection.generated.h"

UCLASS()
class FGGAMEPLAYMATH_API ACubeIntersection : public ADemonstrator
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ACubeIntersection();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere)
	UStaticMesh* CubeMeshRef;

	UPROPERTY(EditAnywhere)
	TArray<UMaterialInterface*> Material;

	UFUNCTION(BlueprintCallable)
	void SetMaterialCube();

	UFUNCTION(BlueprintCallable)
	void RevertMaterialCube();
};
