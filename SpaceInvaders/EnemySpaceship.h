// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"
#include "Projectile.h"
#include "EnemySpaceship.generated.h"


// movimiento y aparicion randomico de naves enemigas por cierto tiempo 

UCLASS()
class SPACEINVADERS_API AEnemySpaceship : public APawn
{
	GENERATED_BODY()

protected:

	UPROPERTY(Category = Mesh, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		class UStaticMeshComponent* EnemySpaceshipMeshComponent;



public:
	// Sets default values for this pawn's properties
	AEnemySpaceship();

	FVector MoveDirection = FVector(1.f, 0.f, 0.f);

	float t;

	UPROPERTY(EditAnywhere)
		float Speed;

	UPROPERTY(Category = Gameplay, EditAnywhere, BlueprintReadWrite)
		FVector GunOffset;

	/* How fast the weapon will fire */
	UPROPERTY(Category = Gameplay, EditAnywhere, BlueprintReadWrite)
		float FireRate;

	UPROPERTY(EditAnywhere, Category = "Spawning")
		float SpawnDelay{ 3.f };

	FTimerHandle TimerHandle_ShotTimerExpired;
	//UPROPERTY(EditAnywhere)
	//	USceneComponent* BulletSpawnPoint;// punto de generacion de la bala

	//UPROPERTY(EditAnywhere, Category = "Component")
	//	class UProjectileMovementComponent* EnemyProjectileMovement;

	//	UPROPERTY(EditAnywhere, Category = "Component")
	//		TSubclassOf<class AProjectile> Bullet_BP;// puntero bullet_BP 
	//private:
	//	const float MaxShootCoolDown = 2.0f;
	//	float ShootCoolDown = 0.0f;
	/* Handler for the fire timer expiry */
	void ShotTimerExpired();

	uint32 bCanFire : 1;

	float FireForwardValue;
	float FireRightValue;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	FORCEINLINE class UStaticMeshComponent* GetEnemySpaceshipMeshComponent() const { return EnemySpaceshipMeshComponent; }
};
	

