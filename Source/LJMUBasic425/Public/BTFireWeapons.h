// Behaviour Tree task that instructs the BaseShip to fire weapons.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTFireWeapons.generated.h"

UCLASS()
class LJMUBASIC425_API UBTFireWeapons : public UBTTaskNode
{
	GENERATED_BODY()

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	
};
