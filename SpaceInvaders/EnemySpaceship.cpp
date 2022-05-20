// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemySpaceship.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/CollisionProfile.h"
#include "UObject/ConstructorHelpers.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"
#include "Projectile.h"

// Sets default values
AEnemySpaceship::AEnemySpaceship()
{
	static ConstructorHelpers::FObjectFinder<UStaticMesh> ShipMesh(TEXT("/Game/TwinStick/Meshes/bixler.bixler"));
	PrimaryActorTick.bCanEverTick = true;
	SetActorScale3D(FVector(10.f, 10.f, 10.f));
	EnemySpaceshipMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("EnemySpaceshipMeshComponent"));
	RootComponent = EnemySpaceshipMeshComponent;
	EnemySpaceshipMeshComponent->SetCollisionProfileName(UCollisionProfile::Pawn_ProfileName);
	EnemySpaceshipMeshComponent->SetStaticMesh(ShipMesh.Object);
	Speed = 40.0f;

	InitialLifeSpan = 7.0f;
	FireRate = 0.5f;
	FireForwardValue = 1.0f;
	FireRightValue = 0.0f;
	GunOffset = FVector(90.f, 0.f, 0.f);
	//BulletSpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("BulletSpawnPoint"));
	//BulletSpawnPoint->SetupAttachment(RootComponent);

	//EnemyProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("EnemyProjectileMovement"));
	//Asi estaba. FloatingMove->SetupAttachment(RootComponent);
}

void AEnemySpaceship::ShotTimerExpired()
{
	bCanFire = true;
}

// Called when the game starts or when spawned
void AEnemySpaceship::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AEnemySpaceship::Tick(float DeltaTime)
{
	
	Super::Tick(DeltaTime);
	

	FVector NewLocation = GetActorLocation();
	NewLocation = NewLocation + (MoveDirection * Speed * DeltaTime * (-2));
	SetActorLocation(NewLocation);


	const FVector FireDirection = FVector(FireForwardValue, FireRightValue, 0.f).GetClampedToMaxSize(1.0f);
	//const FVector FireDirection = GetActorLocation();
	// Try and fire a shot
	
	//FireShot(FireDirection);

	const FRotator FireRotation = FireDirection.Rotation();
	// Spawn projectile at an offset from this pawn
	const FVector SpawnLocation = GetActorLocation() + FireRotation.RotateVector(GunOffset);

	UWorld* const World = GetWorld();
	if (World != nullptr)
	{

		World->SpawnActor<AProjectile>(SpawnLocation, FireRotation);

		//World->SpawnActor<ALaser>(SpawnLocation, FireRotation);
		//UE_LOG(LogTemp, Warning, TEXT("SpawnLocation(X, Y) = %s, %s FireRotation(X, Y) =  s, s"), SpawnLocation.X, SpawnLocation.Y);
		//UE_LOG(LogTemp, Warning, TEXT("World not nullptr"));

	//bCanFire = false;
	//World->GetTimerManager().SetTimer(TimerHandle_ShotTimerExpired, this, &AEnemySpaceship::ShotTimerExpired, FireRate);
	}
}

// Called to bind functionality to input
void AEnemySpaceship::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}



