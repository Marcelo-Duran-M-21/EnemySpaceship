// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyFlyingSpaceship.h"

AEnemyFlyingSpaceship::AEnemyFlyingSpaceship()
{
	static ConstructorHelpers::FObjectFinder<UStaticMesh> ShipMesh(TEXT("/Game/TwinStick/Meshes/Wraith_Raider_Starship.Wraith_Raider_Starship"));
	PrimaryActorTick.bCanEverTick = true;
	EnemySpaceshipMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("EnemySpaceshipMeshComponent2"));
	RootComponent = EnemySpaceshipMeshComponent;
	EnemySpaceshipMeshComponent->SetCollisionProfileName(UCollisionProfile::Pawn_ProfileName);
	EnemySpaceshipMeshComponent->SetStaticMesh(ShipMesh.Object);
	Speed = 80.0f;
}
