// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Spaceship.h"
#include "InventoryComponent2.h"
#include "Colas.h"
#include "MyFlyingSpaceship.generated.h"

/**
 * 
 */
UCLASS()
class SPACEINVADERS_API AMyFlyingSpaceship : public ASpaceship
{
	GENERATED_BODY()
private:

	/** The camera */
	UPROPERTY(Category = Camera, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		class UCameraComponent* CameraComponent;

	/** Camera boom positioning the camera above the character */
	UPROPERTY(Category = Camera, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		class USpringArmComponent* CameraBoom;

	//Colas<class AProjectile*> ColaProyectiles; //CLAVE
	
public:

	AMyFlyingSpaceship();

	virtual void Tick(float DeltaSeconds) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;

	void Fire();
	//void Fire2();

	/* Fire a shot in the specified direction */
	void FireShot(FVector FireDirection);



	/* Handler for the fire timer expiry */
	void ShotTimerExpired();

	/** Offset from the ships location to spawn projectiles */
	UPROPERTY(Category = Gameplay, EditAnywhere, BlueprintReadWrite)
		FVector GunOffset;
	

	/* How fast the weapon will fire */
	UPROPERTY(Category = Gameplay, EditAnywhere, BlueprintReadWrite)
		float FireRate;

	UPROPERTY()
		UInventoryComponent2* MyShipInventory;// creo una variable puntero array para mi nave

	UFUNCTION()

		void DropItem();
		void TakeItem(AInventoryActor* InventoryItem);
		void IncreaseSpeed();
	
	UFUNCTION()

	/*virtual void NotifyHit(class UPrimitiveComponent* MyComp,
		AActor* Other, class UPrimitiveComponent* OtherComp, bool
		bSelfMoved, FVector HitLocation, FVector HitNormal, FVector
		NormalImpulse, const FHitResult& Hit) override;*/

	/** Returns CameraComponent subobject **/
	FORCEINLINE class UCameraComponent* GetCameraComponent() const { return CameraComponent; }
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }


	UFUNCTION()
		void ListarObjetosContenedor();

	UFUNCTION()
		void Setear();

	TMap<FString, int32> MyItems;

	/*TMap<FString, UInventoryComponent2> MyObjectItems;
	TMap<FString,TMap<FString, UInventoryComponent2>> MyObjectItems2;
	TArray<TMap<FString, TMap<FString, UInventoryComponent2>>> MyObjectItems2Array;*/

private:

	/* Flag to control firing  */
	uint32 bCanFire : 1;

	/** Handle for efficient management of ShotTimerExpired timer */
	FTimerHandle TimerHandle_ShotTimerExpired;

	float FireForwardValue;
	float FireRightValue;
	
};
