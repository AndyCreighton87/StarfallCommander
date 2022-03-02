// Fill out your copyright notice in the Description page of Project Settings.


#include "BTFireWeapons.h"

#include "CombatShip.h"
#include "ShipAIController.h"

EBTNodeResult::Type UBTFireWeapons::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AShipAIController* tAIController = Cast<AShipAIController>(OwnerComp.GetAIOwner());

	if (tAIController)
	{
		// Fire Weapons
		const ACombatShip* tOwningShip = Cast<ACombatShip>(tAIController->GetPawn());
		tOwningShip->FireWeapon();

		return EBTNodeResult::Succeeded;
	}

	return EBTNodeResult::Failed;
}
