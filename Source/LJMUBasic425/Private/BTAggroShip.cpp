#include "BTAggroShip.h"

#include "CombatShip.h"
#include "EOrders.h"
#include "ShipAIController.h"
#include "BehaviorTree/BlackboardComponent.h"

EBTNodeResult::Type UBTAggroShip::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AShipAIController* tAIController = Cast<AShipAIController>(OwnerComp.GetAIOwner());

	if(tAIController)
	{
		ACombatShip* tShip = Cast<ACombatShip>(tAIController->GetPawn());

		if (tShip)
		{
			// Set TargetShip and State to Attack
			UBlackboardComponent* tBlackboard = tAIController->GetBlackboardComp();
			tBlackboard->SetValueAsObject("TargetShip", tShip->GetTargetShip());
			tBlackboard->SetValueAsEnum("State", static_cast<uint8>(EOrders::Attack));
			return EBTNodeResult::Succeeded;
		}
	}

	return EBTNodeResult::Failed;
}
