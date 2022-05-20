// Fill out your copyright notice in the Description page of Project Settings.


#include "Wall.h"
#include <iostream>
#include <random>
using namespace std;
AWall::AWall()
{
	PrimaryActorTick.bCanEverTick = true;
	auto MeshAsset = ConstructorHelpers::FObjectFinder<UStaticMesh>(TEXT("/Game/TwinStick/Meshes/SM_Paddle.SM_Paddle"));
	SetActorScale3D(FVector(10.f, 10.f, 10.f));

	if (MeshAsset.Object != nullptr)//Si el mesh object tiene algun valor o no es nulo
									//le devuelve el asset asignado
	{
		GetStaticMeshComponent()->SetStaticMesh(MeshAsset.Object);
		GetStaticMeshComponent()->SetCollisionProfileName(UCollisionProfile::Pawn_ProfileName);
	}
	//GetStaticMeshComponent()->SetMobility(EComponentMobility::Movable);
	SetActorEnableCollision(true);

	//InitialLifeSpan = 3.0f;

}

void AWall::BeginPlay()
{
}

void AWall::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
		
			//	/*int coord1, coord2, coord3;
			//	coord3 = 120;*/
			//	// Initialize the vector with
			//	// initial values as 0
			//	//FVector V(coord1, coord2, coord3);

			//	random_device rd; // obtain a random number from hardware
			//	mt19937 gen(rd()); // seed the generator
			//	uniform_int_distribution<> distr(-400, 400); // define the range

			///*	int quantity = 10;

			//	while (quantity)
			//	{*/
			//		for (int n = 0; n < 10; ++n)
			//			cout << distr(gen) << ' '; // generate numbers

			//		FVector Location(distr(gen), distr(gen), 120.0f);
			//		SpawnCoolDown = 0.0f;

			//		FRotator Rotation(0, 0, 0);
			//		auto object1 = GetWorld()->SpawnActor<AWall>(Location, Rotation);
			//		//quantity--;
			//	//}
	
}
