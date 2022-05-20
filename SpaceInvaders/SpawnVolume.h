// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EnemySpaceship.h"
#include "SpawnVolume.generated.h"


UCLASS()
class SPACEINVADERS_API ASpawnVolume : public AActor
{
	GENERATED_BODY()
public:
    // Sets default values for this actor's properties
    ASpawnVolume();

protected:
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

public:
    // Called every frame
    virtual void Tick(float DeltaTime) override;

    //UPROPERTY(VisibleAnywhere, Category = "Spawing")
    //    class UBoxComponent* WhereToSpawn;//donde generarse

    UPROPERTY(EditAnywhere, Category = "Spawning")//
        TArray<TSubclassOf<AEnemySpaceship>> SpawnClasses;//contenedor TArray para guardar el elemento que atachemos
                                             // en un template TsubclassOf para que reciba solo de ese tipo
    //Actor (Wall ) a atachar desde el motor
    //TArray usamos porque es un template dinamic Array( no tiene dimension definida)
    //TsubClassOf para darle seguridad a mi variable de que en realidad si le voy a pasar un AActor
private:

    float NextSpawnCoolDown = 6.0f;//TIempo hasta siguiente aparicion
    float SpawnCoolDown = 0.0f;//Reseteamos  a 0 para que no aparezcan seguidos los objectos
};
