// Fill out your copyright notice in the Description page of Project Settings.

#include "Pathfinding.h"
#include "Tile.h"


// Sets default values
ATile::ATile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	G = 0;
	H = 0;
	walkable = true;
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh> MyShape(TEXT("/Game/StarterContent/Shapes/Shape_Cube.Shape_Cube"));
	if (MyShape.Succeeded())
	{
		mesh->SetStaticMesh(MyShape.Object);
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("Mesh not found"));
	}
	mesh->AttachTo(RootComponent);
	mesh->SetRelativeScale3D(FVector(2.0, 2.0, 1.0));
}

// Called when the game starts or when spawned
void ATile::BeginPlay()
{
	Super::BeginPlay();
	/*SetActorRotation(FRotator(0, 45.0f, 0));
	FVector RelativeForward = RootComponent->GetForwardVector();
	FString s = FString::FromInt(RelativeForward.X) + " " + FString::FromInt(RelativeForward.Y) + " " + FString::FromInt(RelativeForward.Z);
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Blue, s);*/
}

// Called every frame
void ATile::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );
	walkable = (GetActorScale3D().Z <= 2.0f);
}

int ATile::GetDistanceTo(ATile *tile)
{
	int DX = FMath::Abs(X - tile->X);
	int DY = FMath::Abs(Y - tile->Y);
	if (DX > DY)
		return 14 * DY + 10 * (DX - DY);
	return 14 * DX + 10 * (DY - DX);
}

int ATile::F()
{
	return G + H;
}

bool ATile::CheckObstacle()
{
	FHitResult* Hit = new FHitResult();
	startTrace = GetActorLocation()/* + FVector(GetActorScale3D().X / 2, 0, 0) + FVector(0, GetActorScale3D().Y / 2, 0)*/ + FVector(0, 0, 5 + (GetActorScale3D().Z) * 100);
	endTrace = startTrace + 1000 * FVector(0,0,1);
	FCollisionQueryParams* param = new FCollisionQueryParams();
	if (GetWorld()->LineTraceSingleByChannel(*Hit, startTrace, endTrace, ECC_Visibility, *param))
	{
		DrawDebugLine(GetWorld(), startTrace, endTrace, FColor::Blue, false);
		if (Hit->Actor.Get()){ 
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Black, GetActorLabel() + " - " + Hit->Actor.Get()->GetActorLabel()); 
		}
		else
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Black, "No blocking Actor");
		return true;
	}
	return false;
}



