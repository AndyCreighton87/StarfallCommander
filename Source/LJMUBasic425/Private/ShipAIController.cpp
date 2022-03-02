#include "ShipAIController.h"
#include "BaseShip.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTree.h"


AShipAIController::AShipAIController()
{
	// Setup components
	BehaviorTreeComponent = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("Behavior Tree"));
	BlackboardComponent = CreateDefaultSubobject<UBlackboardComponent>(TEXT("Blackboard"));
}

// Setup Controller
void AShipAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	ABaseShip* tShip = Cast<ABaseShip>(InPawn);

	if (tShip)
	{
		if (tShip->BehaviorTree->BlackboardAsset)
			BlackboardComponent->InitializeBlackboard(*(tShip->BehaviorTree->BlackboardAsset));

		BehaviorTreeComponent->StartTree(*tShip->BehaviorTree);
	}
}


