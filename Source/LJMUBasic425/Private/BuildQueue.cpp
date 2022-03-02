
#include "BuildQueue.h"

#include "BuildQueueWidget.h"
#include "EShipAIState.h"
#include "StarfallPlayerController.h"
#include "UIMainWidget.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"

void ABuildQueue::BeginPlay()
{
	Super::BeginPlay();
	
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;

	// Get a reference to the resource manager.
	// This presented a glaring issue late in development, that the dependency upon the resource manager is entirely reliant upon a Player Controller
	// being in charge of the unit that possesses the Build Queue. When I tried to add a build queue for the AI, I ran into problems as it did not have
	// its own resource manager. If this was earlier in development, I would have fixed it (probably by removing this class from the Player Controller, and
	// creating my own class that could represent either a player or AI within the game that would house the resource manager). 
	AStarfallPlayerController* tPlayerController = Cast<AStarfallPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	ResourceManager = tPlayerController->GetResourceManager();

	// Set up Build Queue Timer
	BuildQueueTimerDelegate.BindLambda([this]
	{
		if (this || !IsPendingKill())
			OnFinishConstruction();
	});
}

void ABuildQueue::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (GetWorld()->GetTimerManager().TimerExists(BuildQueueTimer))
	{
		// Elapsed time / build time
		BuildQueueWidget->UpdateProgressBar(GetWorld()->GetTimerManager().GetTimerElapsed(BuildQueueTimer) / ActiveItem.BuildTime);
	}
}

void ABuildQueue::Init(TScriptInterface<IBuilder> pBuilder)
{
	Builder = pBuilder;
}

TScriptInterface<IBuildable> ABuildQueue::CreateBuildable(FBuildableData pBuildable)
{
	// The intention of the factory and the build queue was to be able to create any
	// IBuildable in the game. At current this is not possible, only ships can be consturcted
	// through this build queue. However due to using an abstract factory an additional factory/build
	// queue could be constructed for any other buildables required. While this is a straightforward
	// implementation, I believe it would benefit from further abstraction.
	
	// Spawn a ship at the Builders location
	const AActor* tActor = Cast<AActor>(Builder.GetObject());
	const FVector tPos = tActor->GetActorLocation();
	const FRotator tRot = tActor->GetActorRotation();
	const FActorSpawnParameters tActorSpawnParms;

	const auto tBuildable = GetWorld()->SpawnActor<ABaseShip>(pBuildable.BuildableClass, tPos, tRot, tActorSpawnParms);

	//Move to spawned ship to the rally point.
	tBuildable->Blackboard->SetValueAsVector("TargetLocation", Builder->GetRallyPointPos());
	tBuildable->Blackboard->SetValueAsEnum("State", static_cast<uint8>(EShipAIState::OnSpawn));
	return tBuildable;
}

// Attempts to add an item to the build queue. Returns false is there is no room in build queue or if the player does
// not have enough resources.
bool ABuildQueue::AddToBuildQueue(FBuildableData pBuildable)
{
	// Do not add to queue if player does not have required resources
	if (BuildQueueCount + 1 <= BuildQueueMaxSize && CheckResources(pBuildable))
	{
		BuildQueue.Add(pBuildable);

		if (BuildQueueCount == 0)
			StartBuildingItem(pBuildable);

		BuildQueueCount++;

		// Deduct resources
		ResourceManager->DeductMinerals(pBuildable.MineralCost);
		ResourceManager->IncreasePopulation(pBuildable.PopulationCost);
		UpdateBuildQueueUI();
		return true;
	}

	BuildQueueWidget->DisplayWarning();
	return false;
}

void ABuildQueue::RemoveFromBuildQueue()
{
	BuildQueue.RemoveAt(0);
	BuildQueueCount--;
}

// Sets the active item in the queue and starts the timer equal to the ships build time
void ABuildQueue::StartBuildingItem(FBuildableData pBuildable)
{
	bIsBuilding = true;
	ActiveItem = pBuildable;
	GetWorld()->GetTimerManager().SetTimer(BuildQueueTimer, BuildQueueTimerDelegate, pBuildable.BuildTime, true);
}

void ABuildQueue::SetWidget(UUserWidget* pWidget)
{
	if (!BuildQueueWidget)
		BuildQueueWidget = Cast<UBuildQueueWidget>(pWidget);

	UpdateBuildQueueUI();
}

void ABuildQueue::UpdateBuildQueueUI()
{
	if (BuildQueueWidget)
		BuildQueueWidget->Update(BuildQueue);
}

// Cleanup for when the Build Queue is destroyed
void ABuildQueue::EmptyBuildQueue()
{
	const int32 tCount = BuildQueueCount;
	for (int i = 0; i < tCount; i++)
		RemoveFromBuildQueue();
	
	GetWorldTimerManager().ClearTimer(BuildQueueTimer);
}

bool ABuildQueue::CheckResources(FBuildableData pBuildable) const
{
	return ResourceManager->CheckSufficientMinerals(pBuildable.MineralCost) && ResourceManager->CheckPopulationLimit(pBuildable.PopulationCost);
}

// When building is finished, do the following:
// 
// 1. Clear existing timer
// 2. Spawn the ship
// 3. Remove the item from the build queue
// 4. If there are remaining items in the build queue, start building the next
// 5. Update the UI
void ABuildQueue::OnFinishConstruction()
{
	GetWorld()->GetTimerManager().ClearTimer(BuildQueueTimer);
	CreateBuildable(ActiveItem);
	RemoveFromBuildQueue();

	if (BuildQueueCount > 0)
	{
		ActiveItem = BuildQueue[0];
		StartBuildingItem(ActiveItem);
	}
	else
	{
		bIsBuilding = false;
		BuildQueueWidget->UpdateProgressBar(0.0f);
	}

	UpdateBuildQueueUI();
}
