// Fill out your copyright notice in the Description page of Project Settings.

#include "MyProject.h"
#include "MyActor.h"
#include "MazeCreator.h"
#include "SpawnerActor.h"


// Sets default values
ASpawnerActor::ASpawnerActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
}

// Called when the game starts or when spawned
void ASpawnerActor::BeginPlay()
{
	Super::BeginPlay();
	Spawn();
}

// Called every frame
void ASpawnerActor::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

void ASpawnerActor::Spawn()
{
	UWorld* const world = GetWorld();
	if (world != NULL)
	{
		for (int i = 0; i < 29; i++)
		{
			for (int j = 0; j < 29; j++)
			{
				AMyActor *A = world->SpawnActor<AMyActor>(myActor, FVector(300.0f * j, 300.0f * i, 60.0f), FRotator(0.0f, 0.0f, 0.0f));
				A->IndexX = j;
				A->IndexY = i;
				
			}
		}

		AMazeCreator *M = world->SpawnActor<AMazeCreator>(myCreator, FVector(200.0f, 200.0f, 120.0f), FRotator(0.0f, 0.0f, 0.0f));
		
	}
	
}

