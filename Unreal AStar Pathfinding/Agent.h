// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Pawn.h"
#include "Agent.generated.h"

UCLASS()
class PATHFINDING_API AAgent : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AAgent();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;

	UPROPERTY(EditAnywhere)
	TArray<class ATile*> myPath;

	UPROPERTY(EditAnywhere)
	class ATile* Begin;

	UPROPERTY(EditAnywhere)
	class ATile* Dest;

	UPROPERTY(EditAnywhere)
	class ATile* prevDest;

	UPROPERTY(EditAnywhere)
	class AGraph* graph;

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* mesh;

	UPROPERTY(EditAnywhere)
	float Dist;

	

	int32 ctr;
};
