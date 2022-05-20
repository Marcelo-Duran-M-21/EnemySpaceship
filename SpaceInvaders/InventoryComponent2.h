// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"

#include "InventoryActor.h"
#include "InventoryComponent2.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SPACEINVADERS_API UInventoryComponent2 : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UInventoryComponent2();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY()
	
	TArray<AInventoryActor*> CurrentInventoryActorsBag;//Creo un contenedor, una bolsa de inventoryactors

	int32 AddToInventory(AInventoryActor* ActorToAdd);

	UFUNCTION()

	void RemoveFromInventory(AInventoryActor* ActorToRemove);
	


		
};
