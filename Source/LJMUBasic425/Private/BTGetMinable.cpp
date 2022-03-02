#include "BTGetMinable.h"

#include "IMinable.h"
#include "ShipAIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"

EBTNodeResult::Type UBTGetMinable::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AShipAIController* tAIController = Cast<AShipAIController>(OwnerComp.GetAIOwner());

	if (tAIController)
	{
		UBlackboardComponent* tBlackboard = tAIController->GetBlackboardComp();

		const APlayerController* tPlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);

		FHitResult tHitResult;
		tPlayerController->GetHitResultUnderCursor(ECollisionChannel::ECC_WorldStatic, false, tHitResult);

		TScriptInterface<IMinable> tMinable = tHitResult.GetActor();

		if (tMinable)
		{
			tBlackboard->SetValueAsObject("TargetMinable", tMinable.GetObject());

			return EBTNodeResult::Succeeded;
		}
	}

	return EBTNodeResult::Failed;
}
