// Fill out your copyright notice in the Description page of Project Settings.


#include "MyFlyingSpaceship.h"
#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"
#include "Projectile.h"
#include "Laser.h"

AMyFlyingSpaceship::AMyFlyingSpaceship()
{
	// Create a camera boom...
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->SetUsingAbsoluteRotation(true); // Don't want arm to rotate when ship does
	CameraBoom->TargetArmLength = 1200.f;
	CameraBoom->SetRelativeRotation(FRotator(-80.f, 0.f, 0.f));
	CameraBoom->bDoCollisionTest = false; // Don't want to pull camera in when it collides with level

	// Create a camera...
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("TopDownCamera"));
	CameraComponent->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	CameraComponent->bUsePawnControlRotation = false;	// Camera does not rotate relative to arm

	// Movement
	MoveSpeed = 1000.0f;

	Energy = 100.0f;

	// Weapon
	GunOffset = FVector(90.f, 0.f, 0.f);
	FireRate = 0.1f;
	bCanFire = false;

	FireForwardValue = 1.0f;
	FireRightValue = 0.0f;


	//const FVector MoveDirection = FVector(FireForwardValue, FireRightValue, 0.f).GetClampedToMaxSize(1.0f);
	//
	//const FRotator FireRotation = MoveDirection.Rotation();
	// Spawn projectile at an offset from this pawn
	//const FVector SpawnLocation = GetActorLocation() + FireRotation.RotateVector(GunOffset);
	//
	//UWorld* const World = GetWorld();
	//if (World != nullptr)
	//{
	//	//FTransform SpawnLocation;
	//	// spawn the projectile
	//	ColaProyectiles.Push(World->SpawnActor<AProjectile>(SpawnLocation, FireRotation));
	//
	//UE_LOG(LogTemp, Warning, TEXT("SpawnLocation(X, Y) = %s, %s FireRotation(X, Y) =  s, s"), SpawnLocation.X, SpawnLocation.Y);
		//UE_LOG(LogTemp, Warning, TEXT("World not nullptr"));
	//}

	MyShipInventory = CreateDefaultSubobject<UInventoryComponent2>("MyInventory");

	MyItems.Add("Vida", 0);
	MyItems.Add("Combustible", 0);
	MyItems.Add("Velocidad", 0);
	MyItems.Add("Bomba", 0);
}

void AMyFlyingSpaceship::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	check(PlayerInputComponent);

	// set up gameplay key bindings
	PlayerInputComponent->BindAxis(MoveForwardBinding);
	PlayerInputComponent->BindAxis(MoveRightBinding);
	//PlayerInputComponent->BindAction(Fire)
	InputComponent->BindAction(TEXT("Fire"), IE_Pressed, this, &AMyFlyingSpaceship::Fire);
	InputComponent->BindAction("DropItem",EInputEvent::IE_Pressed, this,&AMyFlyingSpaceship::DropItem);
	InputComponent->BindAction("Listar", EInputEvent::IE_Pressed, this, &AMyFlyingSpaceship::ListarObjetosContenedor);
	PlayerInputComponent->BindAction("Setear", EInputEvent::IE_Pressed, this, &AMyFlyingSpaceship::Setear);
	PlayerInputComponent->BindAction("IncreaseSpeed", EInputEvent::IE_Pressed, this, &AMyFlyingSpaceship::IncreaseSpeed);

	//PlayerInputComponent->BindAction(FireBinding);
	//PlayerInputComponent->BindAxis(FireForwardBinding);
	//PlayerInputComponent->BindAxis(FireRightBinding);
}

void AMyFlyingSpaceship::Tick(float DeltaSeconds)
{

	// Find movement direction
	const float ForwardValue = GetInputAxisValue(MoveForwardBinding);
	const float RightValue = GetInputAxisValue(MoveRightBinding);

	if (ForwardValue != 0.0f || RightValue != 0.0f) {

		if (ForwardValue != FireForwardValue) {
			FireForwardValue = ForwardValue;
		}

		if (RightValue != FireRightValue) {
			FireRightValue = RightValue;
		}
	}

	//UE_LOG(LogTemp, Warning, TEXT("ForwardValue: %f RightValue: %f"), ForwardValue, RightValue);

	// Clamp max size so that (X=1, Y=1) doesn't cause faster movement in diagonal directions
	const FVector MoveDirection = FVector(ForwardValue, RightValue, 0.f).GetClampedToMaxSize(1.0f);

	// Calculate  movement
	const FVector Movement = MoveDirection * MoveSpeed * DeltaSeconds;

	// If non-zero size, move this actor
	if (Movement.SizeSquared() > 0.0f)
	{
		const FRotator NewRotation = Movement.Rotation();
		FHitResult Hit(1.f);
		RootComponent->MoveComponent(Movement, NewRotation, true, &Hit);

		if (Hit.IsValidBlockingHit())
		{
			const FVector Normal2D = Hit.Normal.GetSafeNormal2D();
			const FVector Deflection = FVector::VectorPlaneProject(Movement, Normal2D) * (1.f - Hit.Time);
			RootComponent->MoveComponent(Deflection, NewRotation, true);
		}
	}
}

void AMyFlyingSpaceship::ShotTimerExpired()
{
	bCanFire = true;
}

void AMyFlyingSpaceship::DropItem()
{
	if (MyShipInventory->CurrentInventoryActorsBag.Num() == 0)//si mi bolsa de de actores esta vacia
	{
		return;
	}
	AInventoryActor* UltimoItem = MyShipInventory->CurrentInventoryActorsBag.Last();
	MyShipInventory->RemoveFromInventory(UltimoItem);

	FVector ItemOrigin;
	FVector ItemBounds;
	UltimoItem->GetActorBounds(false, ItemOrigin, ItemBounds);
	FTransform PutDownLocation = GetTransform() + FTransform(RootComponent->GetForwardVector() * ItemBounds.GetMax());
	UltimoItem->PutDown(PutDownLocation);

}

void AMyFlyingSpaceship::TakeItem(AInventoryActor* InventoryItem)
{
	InventoryItem->PickUp();
	MyShipInventory->AddToInventory(InventoryItem);
}

void AMyFlyingSpaceship::IncreaseSpeed()
{
	FString s = "Velocidad";

		for (auto& pair : MyItems)
		{
			if (pair.Key == s)
			{
				pair.Value = pair.Value -1;
				MoveSpeed += 250;
				break;
			}
		}
	
}

//void AMyFlyingSpaceship::NotifyHit(UPrimitiveComponent* MyComp, AActor* Other, UPrimitiveComponent* OtherComp, bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit)
//{
//	AInventoryActor* InventoryItem = Cast<AInventoryActor>(Other);
//	FString n = InventoryItem->GetNombre();
//	if (InventoryItem != nullptr)
//
//	{
//		for (auto& pair : MyItems)
//		{
//			if (pair.Key == n)
//			{
//				pair.Value = pair.Value + 1;
//				break;
//			}
//		}
//
//		TakeItem(InventoryItem);
//	}
//}

void AMyFlyingSpaceship::ListarObjetosContenedor()
//{	//1er metodo
// 
//	for (int i = 0; i < MyShipInventory->CurrentInventoryActorsBag.Num(); i++) 
//	{
//		GEngine->AddOnScreenDebugMessage(2, 2, FColor::Blue, FString::Printf(TEXT("Actor de nombre : %s"), *(MyShipInventory->CurrentInventoryActorsBag[i]->GetNombre())));
//		//manera antigua de recorrer, con un contador
//	}

	//Segundo Metodo
	// 
	//for (TArray<AInventoryActor* >::TIterator It(MyShipInventory->CurrentInventoryActorsBag);It;++It)
	//{
	//	FString n = Cast<AInventoryActor>(*It)->GetNombre();
	//	GEngine->AddOnScreenDebugMessage(3, 2, FColor::Orange, FString::Printf(TEXT("Actor de nombre : %s"), *n));
	//}

	//3er Metodo


	/*for (auto It = MyShipInventory->CurrentInventoryActorsBag.CreateConstIterator(); It; ++It)
	{
		GEngine->AddOnScreenDebugMessage(3, 2, FColor::Green, FString::Printf(TEXT("Actor de nombre : %s"), *(Cast<AInventoryActor>(*It)->GetNombre())));
	}*/


	//Ejemplo TMap

{
	int count = 0;
	for (TMap<FString, int32>::TIterator it = MyItems.CreateIterator(); it; ++it)
	{
		GEngine->AddOnScreenDebugMessage(count++, 5, FColor::Red,it->Key + FString(": ") + FString::FromInt(it->Value));
	}

}

void AMyFlyingSpaceship::Setear()
{
	TSet<int> setEjemplo;

	setEjemplo.Add(1);
	setEjemplo.Add(10);
	setEjemplo.Add(100);
	setEjemplo.Add(1);// duplicate! won't be added
	setEjemplo.Add(10);// duplicate! won't be added

	int count = 0; // keep track of numerical index in set
	for (TSet<int>::TIterator it = setEjemplo.CreateIterator(); it; ++it)
	{
		GEngine->AddOnScreenDebugMessage(count++, 2, FColor::Cyan,FString::FromInt(*it));
	}
}


void AMyFlyingSpaceship::Fire()
{
	bCanFire = true;
	UE_LOG(LogTemp, Warning, TEXT("Se presiono la barra espaciadora"));
	// Create fire direction vector

	UE_LOG(LogTemp, Warning, TEXT("FireForwardValue: %f FireRightValue: %f"), FireForwardValue, FireRightValue);
	const FVector FireDirection = FVector(FireForwardValue, FireRightValue, 0.f).GetClampedToMaxSize(1.0f);
	//const FVector FireDirection = GetActorLocation();
	// Try and fire a shot
	FireShot(FireDirection);
}




void AMyFlyingSpaceship::FireShot(FVector FireDirection)
{
	// If it's ok to fire again
	if (bCanFire == true)
	{

		// If we are pressing fire stick in a direction
		//if (FireDirection.SizeSquared() > 0.0f)
		//{
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
		}
		//bCanFire = false;
		World->GetTimerManager().SetTimer(TimerHandle_ShotTimerExpired, this, &AMyFlyingSpaceship::ShotTimerExpired, FireRate);

		// try and play the sound if specified

	/*	if (FireSound != nullptr)
		{
			UGameplayStatics::PlaySoundAtLocation(this, FireSound, GetActorLocation());
		}*/

		bCanFire = false;
		//}
	}
}


