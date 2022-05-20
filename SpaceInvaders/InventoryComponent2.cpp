// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryComponent2.h"

// Sets default values for this component's properties
UInventoryComponent2::UInventoryComponent2()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UInventoryComponent2::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UInventoryComponent2::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

int32 UInventoryComponent2::AddToInventory(AInventoryActor* ActorToAdd)
{
	return CurrentInventoryActorsBag.Add(ActorToAdd);
}

void UInventoryComponent2::RemoveFromInventory(AInventoryActor* ActorToRemove)
{
	CurrentInventoryActorsBag.Remove(ActorToRemove);
}

