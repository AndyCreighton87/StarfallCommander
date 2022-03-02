/// The ShipAIController is the base class for all AI Controllers within the game.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "ShipAIController.generated.h"

UCLASS()
class LJMUBASIC425_API AShipAIController : public AAIController
{
	GENERATED_BODY()

	AShipAIController();

	// Components
	UBehaviorTreeComponent* BehaviorTreeComponent;

	UBlackboardComponent* BlackboardComponent;

	// Virtual function inherited from AIController
	virtual void OnPossess(APawn* InPawn) override;

public:
	FORCEINLINE UBlackboardComponent* GetBlackboardComp() const { return BlackboardComponent; }
	
};
