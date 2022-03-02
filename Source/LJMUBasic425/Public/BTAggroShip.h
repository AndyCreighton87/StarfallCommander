/// A Behaviour Tree task that sets the value of TargetShip and the State to attack
/// As a result, the pawn will begin to pursue the TargetShip, firing upon it once
/// it gets into range.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTAggroShip.generated.h"

UCLASS()
class LJMUBASIC425_API UBTAggroShip : public UBTTaskNode
{
	GENERATED_BODY()

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	
};
