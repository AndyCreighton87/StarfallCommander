/// Behaviour Tree Task that sets the value of TargetShip to the ship that is currently below
/// the mouse cursor (if any).
#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTGetTargetShip.generated.h"

/**
 * 
 */
UCLASS()
class LJMUBASIC425_API UBTGetTargetShip : public UBTTaskNode
{
	GENERATED_BODY()
	
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	
};
