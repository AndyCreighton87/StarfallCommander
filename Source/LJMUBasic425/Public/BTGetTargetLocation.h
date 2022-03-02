/// Behaviour Tree task that sets the value of Target Location to the world position
/// of the mouse cursor.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTGetTargetLocation.generated.h"

UCLASS()
class LJMUBASIC425_API UBTGetTargetLocation : public UBTTaskNode
{
	GENERATED_BODY()

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	
};
