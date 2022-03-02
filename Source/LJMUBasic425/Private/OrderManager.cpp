#include "OrderManager.h"

#include "Order.h"
#include "StarfallPlayerController.h"
#include "Kismet/GameplayStatics.h"

AOrderManager::AOrderManager()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AOrderManager::BeginPlay()
{
	Super::BeginPlay();
}

void AOrderManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AOrderManager::AddOrderToPending(AOrder* pOrder)
{
	// If this if the first time pending orders has been called -
	// Change state in player controller to IssueOrder
	if (PendingOrders.Num() == 0)
	{
		AStarfallPlayerController* PlayerController = Cast<AStarfallPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
		PlayerController->SetPlayerInputState(EPlayerInputStates::IssueOrder);
		bIsCurrentlyIssuingOrder = true;
	}
	
	PendingOrders.Add(pOrder);
}

// Release all pending orders
void AOrderManager::ExecutePendingOrders()
{
	bIsCurrentlyIssuingOrder = false;
	
	for (const auto entry : PendingOrders)
		entry->OnActivate();
	
	ClearPendingOrders();
}

void AOrderManager::ClearPendingOrders()
{
	PendingOrders.Empty();
}

