// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyGroundSpaceship.h"

AEnemyGroundSpaceship::AEnemyGroundSpaceship()
{
	static ConstructorHelpers::FObjectFinder<UStaticMesh> ShipMesh(TEXT("/Game/TwinStick/Meshes/Yoshi5.Yoshi5"));
	PrimaryActorTick.bCanEverTick = true;
	EnemySpaceshipMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("EnemySpaceshipMeshComponent3"));
	RootComponent = EnemySpaceshipMeshComponent;
	EnemySpaceshipMeshComponent->SetCollisionProfileName(UCollisionProfile::Pawn_ProfileName);
	EnemySpaceshipMeshComponent->SetStaticMesh(ShipMesh.Object);
	Speed = 8.0f;
}
