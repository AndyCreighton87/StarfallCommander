// Fill out your copyright notice in the Description page of Project Settings.


#include "BTSetWeaponCooldown.h"

#include "CombatShip.h"
#include "ShipAIController.h"
#include "BehaviorTree/BlackboardComponent.h"

EBTNodeResult::Type UBTSetWeaponCooldown::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AShipAIController* tAIController = Cast<AShipAIController>(OwnerComp.GetAIOwner());

	if (tAIController)
	{
		ACombatShip* tOwningShip = Cast<ACombatShip>(tAIController->GetPawn());
		const float tValue = tOwningShip->GetWeaponCooldown();

		UBlackboardComponent* tBlackboard = tAIController->GetBlackboardComp();
		tBlackboard->SetValueAsFloat("WeaponCooldown", tValue);

		return EBTNodeResult::Succeeded;
	}

	return EBTNodeResult::Failed;
}
