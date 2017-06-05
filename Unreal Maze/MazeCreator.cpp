// Fill out your copyright notice in the Description page of Project Settings.

#include "MyProject.h"
#include "MyActor.h"
#include "MazeCreator.h"


// Sets default values
AMazeCreator::AMazeCreator()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	/**/
	TimerToStartTick = 0.0f;
	Created = false;
	CompleteVisit = false;
	Init = false;
}

// Called when the game starts or when spawned
void AMazeCreator::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMazeCreator::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (TimerToStartTick < 0.1f)
	{
		TimerToStartTick += DeltaTime;
	}
	else
	{
		if (!Init)
		{
			for (TActorIterator<AMyActor> MyActorItr(GetWorld()); MyActorItr; ++MyActorItr)
			{
				if (MyActorItr->Tag == "NO WALL")
				{
					PathsList.Add(*MyActorItr);
				}
				if (MyActorItr->IndexX == 1 && MyActorItr->IndexY == 1)
				{
					current = *MyActorItr;
				}
			}
		
			Init = true;
		}
		else if (Init & !Created)
		{
			MazeTimer += DeltaTime;
			if (MazeTimer >= 0.0f)
			{
				CreateMaze();
				MazeTimer = 0.0f;
			}
		}
	}
}

bool AMazeCreator::AllPathsVisited()
{
	for (int i = 0; i < PathsList.Num(); i++)
	{
		if (!PathsList[i]->Visited)
		{
			return false;
		}
	}
	return true;
}

inline void AMazeCreator::CreateMaze()
{
	current->Visited = true;
	current->MazeStatus = "PATH";
	CompleteVisit = AllPathsVisited();
	
	if (!CompleteVisit)
	{
	
		for (int i = 0; i < current->Neighbours.Num(); i++)
		{
			if (current->Neighbours[i]->MazeStatus == "DEFAULT")
			{
				current->Neighbours[i]->MazeStatus = "FRONTIER";
				current->Neighbours[i]->PathOpener = current;
				FrontierList.Add(current->Neighbours[i]);
			}
		}

		if (FrontierList.Num() > 0)
		{
			RandFactor = FMath::RandRange(0, FrontierList.Num() - 1);
				for (int j = 0; j < FrontierList[RandFactor]->PathOpener->Connectors.Num(); j++)
				{
					if (FrontierList[RandFactor]->Connectors.Contains(FrontierList[RandFactor]->PathOpener->Connectors[j]))
					{
						FrontierList[RandFactor]->PathOpener->Connectors[j]->DisableTile();
						break;
					}
				}
			current = FrontierList[RandFactor];
			FrontierList.RemoveAt(RandFactor);
		}
	}
	else
	{
		Created = true;
		return;
	}
	
}

