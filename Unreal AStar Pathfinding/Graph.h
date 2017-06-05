// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Graph.generated.h"

UCLASS()
class PATHFINDING_API AGraph : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGraph();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	UPROPERTY(EditAnywhere)
	TArray<class ATile*> neighbours;

	UPROPERTY(EditAnywhere)
	TArray<class ATile*> Path;

	TArray<class ATile*> GetPath(ATile* start, ATile* end);
	TArray<class ATile*> RetracePath(ATile* start, ATile* end);
	TArray<ATile*> GetNeigbours(ATile& t);

	TArray<TArray<class ATile*>> allTiles;

	UPROPERTY(EditAnywhere)
	int32 maxX;

	UPROPERTY(EditAnywhere)
	int32 maxY;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class ATile> spawnedTile;

	ATile* GetTile(int x, int y);
};
