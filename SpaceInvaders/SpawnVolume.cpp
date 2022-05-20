// Fill out your copyright notice in the Description page of Project Settings.


#include "SpawnVolume.h"
#include "Components/BoxComponent.h"
#include <iostream>
#include <random>
#include "Wall.h"
#include "EnemySpaceship.h"
using namespace std;
// Sets default values
ASpawnVolume::ASpawnVolume()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ASpawnVolume::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASpawnVolume::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    if (SpawnClasses.Num() <= 0)//Contenedor vacio no devuelve nada
    {
        return;
    }
    const int Index = FMath::RandRange(0, SpawnClasses.Num() - 1);//Rango del indice que va desde 0 hasta 
                                                                    //el tamano de mi contenedor
    SpawnCoolDown = SpawnCoolDown + DeltaTime;
    if (SpawnCoolDown >= NextSpawnCoolDown)
    {
        random_device rd; // obtain a random number from hardware
        mt19937 gen(rd()); // seed the generator ( Generador de números pseudoaleatorios )
        uniform_int_distribution<> distr(-400, 400); // define the range

        for (int n = 0; n < 50; ++n)
        cout << distr(gen); // generate numbers

        FVector Location(distr(gen), distr(gen), 120.0f);
        SpawnCoolDown = 0.0f;//Reseteamos  a 0 para que no aparezcan seguidos los objectos
        FRotator Rotation(0, distr(gen), 0);
        GetWorld()->SpawnActor(SpawnClasses[Index], &Location, &Rotation);
        //Aqui se realiza la invocacion de las paredes, considerando Location, Rotation, y el indice del contenedor


     /*   FVector Location = WhereToSpawn->GetComponentLocation();
        float Y = WhereToSpawn->GetScaledBoxExtent().Y;
        Location.Y = FMath::RandRange(Location.Y - Y, Location.Y + Y);



        SpawnCoolDown = 0.0f;
        FRotator Rotation = GetActorRotation();
        Rotation.Pitch = 180.0;

        GetWorld()->SpawnActor(SpawnClasses[Index], &Location, &Rotation);*/

    }

}

