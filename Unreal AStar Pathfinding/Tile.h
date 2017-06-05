// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Tile.generated.h"

UCLASS()
class PATHFINDING_API ATile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATile();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	UPROPERTY(EditAnywhere)
	int32 X;

	UPROPERTY(EditAnywhere)
	int32 Y;

	int F();
	int G;
	int H;

	UPROPERTY(EditAnywhere)
	bool walkable;
	
	int GetDistanceTo(ATile *tile);

	UPROPERTY(EditAnywhere)
	ATile* parent;

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* mesh;

	UPROPERTY(EditAnywhere)
	FVector startTrace;

	UPROPERTY(EditAnywhere)
	FVector endTrace;

	bool CheckObstacle();
};
