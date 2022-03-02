/// Behaviour tree task that sets the value of TargetMinable, designed to be used
/// to issue a Mine order to a Miner.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTGetMinable.generated.h"

/**
 * 
 */
UCLASS()
class LJMUBASIC425_API UBTGetMinable : public UBTTaskNode
{
	GENERATED_BODY()

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	
};
