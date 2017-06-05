// Fill out your copyright notice in the Description page of Project Settings.

#include "Pathfinding.h"
#include "Tile.h"
#include "Graph.h"
#include "Agent.h"


// Sets default values
AAgent::AAgent()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	mesh->AttachTo(RootComponent);
}

// Called when the game starts or when spawned
void AAgent::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AAgent::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );
	//myPath.Empty();
	Begin = graph->GetTile(0, 0);
	Dest = graph->GetTile(18, 16);
	if (myPath.Num() == 0 /*|| prevDest != Dest*/){
		myPath = graph->GetPath(Begin, Dest);
		ctr = myPath.Num() - 1;
	}

	if (GetActorLocation().X < myPath[ctr]->GetActorLocation().X){
		SetActorLocation(FVector(GetActorLocation().X + 4, GetActorLocation().Y, GetActorLocation().Z));
	}
	if (GetActorLocation().X > myPath[ctr]->GetActorLocation().X){
		SetActorLocation(FVector(GetActorLocation().X - 4, GetActorLocation().Y, GetActorLocation().Z));
	}
	if (GetActorLocation().Y < myPath[ctr]->GetActorLocation().Y){
		SetActorLocation(FVector(GetActorLocation().X, GetActorLocation().Y + 4, GetActorLocation().Z));
	}
	if (GetActorLocation().Y > myPath[ctr]->GetActorLocation().Y){
		SetActorLocation(FVector(GetActorLocation().X, GetActorLocation().Y - 4, GetActorLocation().Z));
	}
	Dist = FVector::Dist(GetActorLocation(), myPath[ctr]->GetActorLocation());
	if (Dist < 80.0f && ctr > 0){
		ctr--;
	}
	//prevDest = Dest;
}

// Called to bind functionality to input
void AAgent::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);

}


