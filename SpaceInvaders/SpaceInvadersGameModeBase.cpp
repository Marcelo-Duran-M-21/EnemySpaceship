// Copyright Epic Games, Inc. All Rights Reserved.


#include "SpaceInvadersGameModeBase.h"
#include "EnemySpaceship.h"
#include "Wall.h"
#include <iostream>
#include <random>


using namespace std;
ASpaceInvadersGameModeBase::ASpaceInvadersGameModeBase()
{
}

void ASpaceInvadersGameModeBase::BeginPlay()
{
	//int coord1, coord2, coord3;
	//coord3 = 120;
	//// Initialize the vector with
	//// initial values as 0
	//FVector V(coord1, coord2, coord3);

	//random_device rd; // obtain a random number from hardware
	//mt19937 gen(rd()); // seed the generator
	//uniform_int_distribution<> distr(-400, 400); // define the range
	//int quantity = 10;
	//while (quantity) {


	//	for (int n = 0; n < 10; ++n)
	//		cout << distr(gen) << ' '; // generate numbers

	//	FVector Location(distr(gen), distr(gen), 120.0f);

	//	FRotator Rotation(0, 0, 0);
	//	auto object1 = GetWorld()->SpawnActor<AWall>(Location, Rotation);
	//	if (object1->InitialLifeSpan == 0)
	//		quantity--;

	//}

	
}

void ASpaceInvadersGameModeBase::Tick(float DeltaSeconds)
{

}
