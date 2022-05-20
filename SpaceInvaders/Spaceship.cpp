// Fill out your copyright notice in the Description page of Project Settings.


#include "Spaceship.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/CollisionProfile.h"
#include "UObject/ConstructorHelpers.h"

const FName ASpaceship::MoveForwardBinding("MoveForward");
const FName ASpaceship::MoveRightBinding("MoveRight");
const FName ASpaceship::FireBinding("Fire");

// Sets default values

ASpaceship::ASpaceship()
{
	static ConstructorHelpers::FObjectFinder<UStaticMesh> ShipMesh(TEXT("/Game/TwinStick/Meshes/TwinStickUFO.TwinStickUFO"));
	PrimaryActorTick.bCanEverTick = true;

	SpaceshipMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SpaceshipMesh"));
	RootComponent = SpaceshipMeshComponent;

	SpaceshipMeshComponent->SetCollisionProfileName(UCollisionProfile::Pawn_ProfileName);
	SpaceshipMeshComponent->SetStaticMesh(ShipMesh.Object);

}

// Called when the game starts or when spawned
void ASpaceship::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASpaceship::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ASpaceship::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

