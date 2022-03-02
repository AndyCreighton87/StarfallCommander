/// Behaviour Tree task that sets the Blackboard Value of WeaponCooldown equal to that of the
/// owning ship. There may have been a better way to do this?

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTSetWeaponCooldown.generated.h"

UCLASS()
class LJMUBASIC425_API UBTSetWeaponCooldown : public UBTTaskNode
{
	GENERATED_BODY()

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	
};
