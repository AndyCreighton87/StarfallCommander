

#include "ResourceManager.h"

#include "ResourceWidget.h"
#include "Kismet/GameplayStatics.h"

AResourceManager::AResourceManager()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AResourceManager::BeginPlay()
{
	Super::BeginPlay();
}

void AResourceManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Set starting values & setup custom tick
void AResourceManager::Init()
{
	Minerals = StartingMinerals;

	// Mineral tick set to 1 tick per second.
	constexpr float tCustomTickTimeStep = 1.0f;
	FTimerDelegate tTimerDelegate;
	tTimerDelegate.BindLambda([this]
	{
		MineralTick();
	});
	
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, tTimerDelegate, tCustomTickTimeStep, true);
}

// *Note: I didn't comment on any further functions in this class as I believe them to
// be pretty self-explanatory. The only thing worth mentioning is that when any form of
// resource is updated, the ResourceUpdateDelegate is broadcast with the intention of updating
// the UI.

void AResourceManager::DeductMinerals(int32 pAmount)
{
	if (Minerals - pAmount >= 0)
	{
		Minerals -= pAmount;
		ResourcesUpdatedDelegate.Broadcast(Minerals, MineralTickValue, CurrentPopulation, PopulationLimit);
	}
}

void AResourceManager::AddMinerals(int32 pAmount)
{
	Minerals += pAmount;
	ResourcesUpdatedDelegate.Broadcast(Minerals, MineralTickValue, CurrentPopulation, PopulationLimit);
}

bool AResourceManager::CheckPopulationLimit(int32 pPopCost)
{
	return CurrentPopulation + pPopCost <= PopulationLimit;
}

bool AResourceManager::CheckSufficientMinerals(int32 pCost)
{
	return Minerals - pCost >= 0;
}

void AResourceManager::IncreaseMineralTick()
{
	MineralTickValue++;
}

void AResourceManager::DecreaseMineralTick()
{
	if (MineralTickValue > 0)
		MineralTickValue--;
}

void AResourceManager::IncreasePopulation(int32 pAmount)
{
	CurrentPopulation += pAmount;
	ResourcesUpdatedDelegate.Broadcast(Minerals, MineralTickValue, CurrentPopulation, PopulationLimit);
}

void AResourceManager::DecreasePopulation(int32 pAmount)
{
	if(CurrentPopulation - pAmount >= 0)
	{
		CurrentPopulation -= pAmount;
		ResourcesUpdatedDelegate.Broadcast(Minerals, MineralTickValue, CurrentPopulation, PopulationLimit);

	}
}

void AResourceManager::MineralTick()
{
	AddMinerals(MineralTickValue);
}

