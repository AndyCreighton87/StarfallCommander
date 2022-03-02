// Fill out your copyright notice in the Description page of Project Settings.


#include "BTSetToIdle.h"

#include "EShipAIState.h"
#include "ShipAIController.h"
#include "BehaviorTree/BlackboardComponent.h"

EBTNodeResult::Type UBTSetToIdle::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AShipAIController* tAIController = Cast<AShipAIController>(OwnerComp.GetAIOwner());

	if (tAIController)
	{
		UBlackboardComponent* tBlackboard = tAIController->GetBlackboardComp();
		tBlackboard->SetValueAsEnum("State", 0);
		
		return EBTNodeResult::Succeeded;
	}

	return EBTNodeResult::Failed;
}
