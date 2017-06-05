// Fill out your copyright notice in the Description page of Project Settings.

#include "MyProject.h"
#include "MyActor.h"


// Sets default values
AMyActor::AMyActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("Sphere"));
	RootComponent = BoxComponent;
	//SphereComponent->InitSphereRadius(10.0f);
	MyRoot = BoxComponent;
	
	MyMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Sphere Visual Mesh"));
	
	MyMesh->AttachTo(RootComponent);

	MyMesh->BodyInstance.SetCollisionProfileName("BlockAll");
	MyMesh->SetNotifyRigidBodyCollision(true);
	MyMesh->SetSimulatePhysics(true);

	static ConstructorHelpers::FObjectFinder<UStaticMesh> shape(TEXT("/Game/StarterContent/Shapes/Shape_Cube"));
	if (shape.Succeeded())
	{
		MyMesh->SetStaticMesh(shape.Object);
	}

	SetActorScale3D(FVector(3.0, 3.0, 3.0));
	
	InitializeRelation = false;
	Visited = false;
	MazeStatus = "DEFAULT";
	Name = "GRID ";
	//MyMesh->Rigidbody
}

void AMyActor::DisableTile()
{
	SetActorHiddenInGame(true);
	SetActorTickEnabled(false);
}

// Called when the game starts or when spawned
void AMyActor::BeginPlay()
{
	Name += FString::FromInt(IndexX);
	Name += " ";
	Name += FString::FromInt(IndexY);
	SetActorLabel(Name);
	if (IndexX % 2 != 0 && IndexY % 2 != 0)
	{
		DisableTile();
		Tag = "NO WALL";
	}
	else if (IndexX == 0 || IndexY == 0 || IndexX == 28 || IndexY == 28)
	{
		Tag = "EDGE WALL";
	}
	else if (IndexX % 2 == 0 || IndexY % 2 == 0)
	{
		Tag = "WALL";
	}
}

void AMyActor::Tick( float DeltaTime )
{
	if (Tag == "WALL" && Neighbours.Num() == 2 && !InitializeRelation)
	{
		if (!Neighbours[0]->Neighbours.Contains(Neighbours[1]) && (Neighbours[0]->IndexX == Neighbours[1]->IndexX || Neighbours[0]->IndexY == Neighbours[1]->IndexY))
			Neighbours[0]->Neighbours.Add(Neighbours[1]);
		if (!Neighbours[1]->Neighbours.Contains(Neighbours[0]) && (Neighbours[0]->IndexX == Neighbours[1]->IndexX || Neighbours[0]->IndexY == Neighbours[1]->IndexY))
			Neighbours[1]->Neighbours.Add(Neighbours[0]);
		InitializeRelation = true;
	}
	Super::Tick( DeltaTime );
	
}

void AMyActor::NotifyHit(UPrimitiveComponent *MyComp, AActor *Other, UPrimitiveComponent *OtherComp, bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit)
{
	
	if (Other->IsA(AMyActor::StaticClass()))
	{
		AMyActor *RealActor = Cast<AMyActor>(Other);

		if (Tag == "WALL" && RealActor->Tag == "NO WALL")
		{
			if (!Neighbours.Contains(RealActor))
				this->Neighbours.Add(RealActor);
		}
			
		else if (Tag == "NO WALL" && RealActor->Tag == "WALL" && (this->IndexX == RealActor->IndexX || this->IndexY == RealActor->IndexY))
		{
			if (!Connectors.Contains(RealActor))
				this->Connectors.Add(RealActor);
		}
			
		this->NeighbourTags.Add(RealActor->Tag);
		
	}

}



void AMyActor::TriggerEnter(AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFrowSweep, const FHitResult& hit)
{
	
}

