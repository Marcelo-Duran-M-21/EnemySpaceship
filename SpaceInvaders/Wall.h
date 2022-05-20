// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/StaticMeshActor.h"
#include "Wall.generated.h"

/**
 * 
 */
UCLASS()
class SPACEINVADERS_API AWall : public AStaticMeshActor
{
	GENERATED_BODY()
private:

	/*UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Obstacles", meta = (AllowPrivateAccess = "true"))
		FString WallName;*/

public:

	AWall();


protected:

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	/*virtual void PickUp();

	virtual void PutDown(FTransform TargetLocation);*/

	/*FORCEINLINE FString GetWallName() const { return WallName; }
	FORCEINLINE void SetWallName(FString _WallName) { WallName = _WallName; }*/

};
