// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "SpawnerActor.generated.h"

UCLASS()
class MYPROJECT_API ASpawnerActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASpawnerActor();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	void Spawn();

	UPROPERTY()
	FString myName;

	UPROPERTY(EditAnywhere, Category = Spawning)
	TSubclassOf<class AMyActor> myActor;

	UPROPERTY(EditAnywhere, Category = Spawning)
	TSubclassOf<class AMazeCreator> myCreator;
	
};
