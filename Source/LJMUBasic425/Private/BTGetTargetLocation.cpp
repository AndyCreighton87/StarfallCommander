#include "BTGetTargetLocation.h"
#include "ShipAIController.h"
#include "StarfallPlayerController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"

EBTNodeResult::Type UBTGetTargetLocation::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AShipAIController* tAIController = Cast<AShipAIController>(OwnerComp.GetAIOwner());

	if (tAIController)
	{
		UBlackboardComponent* tBlackboard = tAIController->GetBlackboardComp();
		AStarfallPlayerController* tPlayerController = Cast<AStarfallPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));

		if (tPlayerController)
		{
			// I have tried to use my own custom channel for collision with the floor, however this may have been unnecessary. 
			FHitResult tHitResult;
			tPlayerController->GetHitResultUnderCursor(ECollisionChannel::ECC_GameTraceChannel2, false, tHitResult);
			tBlackboard->SetValueAsVector("TargetLocation", tHitResult.Location);

			return EBTNodeResult::Succeeded;
		}
	}

	return EBTNodeResult::Failed;
}
