// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/StaticMeshActor.h"
#include "InventoryActor.generated.h"

/**
 * 
 */
UCLASS()
class SPACEINVADERS_API AInventoryActor : public AStaticMeshActor
{
	GENERATED_BODY()

private:

	UPROPERTY(EditAnywhere,BlueprintReadWrite , Category = "Datos", meta = (AllowPrivateAccess = "true"))
	FString Nombre;

public:

	AInventoryActor();

protected:

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void PickUp();

	virtual void PutDown(FTransform TargetLocation);

	FORCEINLINE FString GetNombre() const { return Nombre; }
	FORCEINLINE void SetNombre(FString _Nombre) { Nombre = _Nombre; }

};
