// Behavior Tree tasks that sets the current State back to Idle/Stop

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTSetToIdle.generated.h"

UCLASS()
class LJMUBASIC425_API UBTSetToIdle : public UBTTaskNode
{
	GENERATED_BODY()

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	
};
