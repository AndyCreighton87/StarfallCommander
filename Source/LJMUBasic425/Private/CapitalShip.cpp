// Fill out your copyright notice in the Description page of Project Settings.


#include "CapitalShip.h"

#include "BuildQueue.h"

ACapitalShip::ACapitalShip(const FObjectInitializer& ObjectInitializer) : ACombatShip(ObjectInitializer)
{
	// Create Rally Point
	RallyPoint = CreateDefaultSubobject<USceneComponent>(FName("Rally Point"));
	RallyPoint->SetupAttachment(Mesh);
}

void ACapitalShip::BeginPlay()
{
	Super::BeginPlay();

	// Create build queue.
	// Because this is an actor spawned into the world, we have to remember to clean
	// it up when game ends.
	BuildQueue = GetWorld()->SpawnActor<ABuildQueue>();
	BuildQueue->Init(this);
}

TArray<FBuildableData> ACapitalShip::GetBuildables()
{
	return Buildables;
}

ABuildQueue* ACapitalShip::GetBuildQueue()
{
	return BuildQueue;
}

FVector ACapitalShip::GetRallyPointPos()
{
	return RallyPoint->GetComponentLocation();
}

void ACapitalShip::CleanUp()
{
	ClearBuildQueue();
}

void ACapitalShip::ClearBuildQueue() const
{
	// Empty and Destroy build queue
	if (BuildQueue)
	{
		BuildQueue->EmptyBuildQueue();
		BuildQueue->Destroy();
	}
}

void ACapitalShip::ManageDeath()
{
	Super::ManageDeath();
}
