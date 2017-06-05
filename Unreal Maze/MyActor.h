// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "MyActor.generated.h"

UCLASS()
class MYPROJECT_API AMyActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMyActor();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	UPROPERTY(EditAnywhere)
	USceneComponent *MyRoot;

	/*UPROPERTY(EditAnywhere)
	UStaticMeshComponent *floorMesh;*/

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent *MyMesh;

	UPROPERTY(EditAnywhere)
	UBoxComponent *BoxComponent;

	UPROPERTY(EditAnywhere)
		float x;

	UPROPERTY(EditAnywhere)
		int32 IndexX;

	UPROPERTY(EditAnywhere)
		int32 IndexY;

	UPROPERTY(EditAnywhere)
		FString Name;

	UPROPERTY(EditAnywhere)
		FString Tag;

	UPROPERTY(EditAnywhere)
		FString MazeStatus;

	UFUNCTION()
		void NotifyHit(UPrimitiveComponent *MyComp, AActor *Other, UPrimitiveComponent *OtherComp, bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit);

	UFUNCTION()
		void TriggerEnter(AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFrowSweep, const FHitResult& hit);

	UPROPERTY(EditAnywhere, Category = Spawning)
		TArray<AMyActor*> Neighbours;

	UPROPERTY(EditAnywhere, Category = Spawning)
		TArray<FString> NeighbourTags;
	
	UPROPERTY(EditAnywhere, Category = Spawning)
		TArray<AMyActor*> Connectors;

	UPROPERTY(EditAnywhere)
	class AMyActor* PathOpener;

	void DisableTile();

	UPROPERTY(EditAnywhere)
	bool Visited;

	bool InitializeRelation;

	class AMyActor* TempForNeighbour;
	class AMyActor* TempForConnector;


};
