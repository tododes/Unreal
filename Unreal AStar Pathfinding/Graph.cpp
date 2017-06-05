// Fill out your copyright notice in the Description page of Project Settings.

#include "Pathfinding.h"
#include "Tile.h"
#include "Graph.h"


// Sets default values
AGraph::AGraph()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AGraph::BeginPlay()
{
	Super::BeginPlay();
	UWorld* const world = GetWorld();
	TArray<ATile*> tt;
	for (int i = 0; i < maxX; i++)
	{
		tt.Empty();
		for (int j = 0; j < maxY; j++)
		{
			ATile *t = world->SpawnActor<ATile>(spawnedTile, FVector(i * 200, j * 200, 0), FRotator(0, 0, 0));
			t->X = i;
			t->Y = j;
			t->SetActorLabel("Tile " + FString::FromInt(i) + " " + FString::FromInt(j));
			if (i >= 5 && i <= 8 && j >= 5 && j <= 8){
				t->SetActorScale3D(FVector(1, 1, 5));
				t->walkable = false;
			}
				
			if (i >= 7 && i <= 15 && j >= 7 && j <= 15){
				t->SetActorScale3D(FVector(1, 1, 5));
				t->walkable = false;
			}
			tt.Add(t);
		}
		allTiles.Add(tt);
	}
}

// Called every frame
void AGraph::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );
	//Path = GetPath(allTiles[0][0], allTiles[11][17]);
}
TArray<ATile*> AGraph::GetNeigbours(ATile& t)
{
	TArray<ATile*> n;
	for (int i = t.X - 1; i <= t.X + 1; i++)
	{
		for (int j = t.Y - 1; j <= t.Y + 1; j++)
		{
			if ((i < 0 || j < 0 || i > maxX || j > maxY))
				continue;
			else if (i == t.X && j == t.Y)
				continue;
			else
				n.Add(allTiles[i][j]);
		}
	}
	return n;
}

TArray<class ATile*> AGraph::RetracePath(ATile* start, ATile* end)
{
	TArray<class ATile*> p;
	ATile* c = end;
	while (c != start)
	{
		p.Add(c);
		c = c->parent;
	}
	p.Add(start);
	return p;
}

ATile* AGraph::GetTile(int x, int y)
{
	return allTiles[x][y];
}

TArray<class ATile*> AGraph::GetPath(ATile* start, ATile* end)
{
	TArray<class ATile*> p;
	TArray<class ATile*> openList;
	TArray<class ATile*> closedList;
	openList.Add(start);
	ATile* curr = openList[0];
	while (openList.Num() > 0)
	{
		curr = openList[0];
		for (ATile* at : openList)
		{
			if (at->F() <= curr->F() && at->H < curr->H)
				curr = at;
		}
		openList.Remove(curr);
		closedList.Add(curr);
		if (curr == end)
		{
			p = RetracePath(start, end);
			return p;
		}
		for (ATile* a : GetNeigbours(*curr))
		{
			if (!a->walkable || closedList.Contains(a))
				continue;

			int newCost = curr->G + curr->GetDistanceTo(a);
			if (newCost < a->G || !openList.Contains(a))
			{
				a->G = newCost;
				a->H = a->GetDistanceTo(end);
				a->parent = curr;
				if (!openList.Contains(a))
				{
					openList.Add(a);
				}
			}
		}
	}
	return p;
}


