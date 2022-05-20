// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyAcuaticSpaceship.h"

AEnemyAcuaticSpaceship::AEnemyAcuaticSpaceship() 
{
	static ConstructorHelpers::FObjectFinder<UStaticMesh> ShipMesh(TEXT("/Game/TwinStick/Meshes/TwinStickUFO.TwinStickUFO"));
	PrimaryActorTick.bCanEverTick = true;
	EnemySpaceshipMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("EnemySpaceshipMeshComponent1"));
	RootComponent = EnemySpaceshipMeshComponent;
	EnemySpaceshipMeshComponent->SetCollisionProfileName(UCollisionProfile::Pawn_ProfileName);
	EnemySpaceshipMeshComponent->SetStaticMesh(ShipMesh.Object);
	Speed = 20.0f;
}
