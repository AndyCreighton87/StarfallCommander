#include "BTClearTargetShip.h"

#include "CombatShip.h"
#include "ShipAIController.h"
#include "BehaviorTree/BlackboardComponent.h"

EBTNodeResult::Type UBTClearTargetShip::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AShipAIController* tAIController = Cast<AShipAIController>(OwnerComp.GetAIOwner());

	if(tAIController)
	{
		// Clear value of target ship. Needs to be done in both the Blackboard and within the class itself.
		ACombatShip* tShip = Cast<ACombatShip>(tAIController->GetPawn());
		tShip->SetTargetShip(nullptr);
		UBlackboardComponent* tBlackboard = tAIController->GetBlackboardComp();
		tBlackboard->ClearValue("TargetShip");

		return EBTNodeResult::Succeeded;
	}

	return EBTNodeResult::Failed;}
