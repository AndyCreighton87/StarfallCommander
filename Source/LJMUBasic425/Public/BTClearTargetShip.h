/// A Behaviour Tree task that clears the value of TargetShip. Used when the TargetShip
/// has been destroyed.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTClearTargetShip.generated.h"

/**
 * 
 */
UCLASS()
class LJMUBASIC425_API UBTClearTargetShip : public UBTTaskNode
{
	GENERATED_BODY()

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	
};
