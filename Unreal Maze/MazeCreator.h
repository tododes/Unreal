// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "MazeCreator.generated.h"

UCLASS()
class MYPROJECT_API AMazeCreator : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMazeCreator();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	inline void CreateMaze();

	bool AllPathsVisited();

	UPROPERTY(EditAnywhere, Category = MazeGeneration)
	class AMyActor *StartingTile;

	UPROPERTY(EditAnywhere, Category = MazeGeneration)
	class AMyActor *current;

	UPROPERTY(EditAnywhere, Category = MazeGeneration)
		TArray<AMyActor*> FrontierList;

	UPROPERTY(EditAnywhere, Category = MazeGeneration)
		TArray<AMyActor*> PathsList;

	UPROPERTY(EditAnywhere)
		float TimerToStartTick;

	int RandFactor;
	
	UPROPERTY(EditAnywhere)
		bool Created;
	UPROPERTY(EditAnywhere)
		bool CompleteVisit;

	bool Init;
	float MazeTimer;
	
};
