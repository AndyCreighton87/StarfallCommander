#include "BTGetTargetShip.h"

#include "BaseShip.h"
#include "CombatShip.h"
#include "ShipAIController.h"
#include "StarfallPlayerController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"

EBTNodeResult::Type UBTGetTargetShip::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AShipAIController* tAIController = Cast<AShipAIController>(OwnerComp.GetAIOwner());

	if (tAIController)
	{
		UBlackboardComponent* tBlackboard = tAIController->GetBlackboardComp();

		AStarfallPlayerController* tPlayerController = Cast<AStarfallPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));

		if (tPlayerController)
		{
			// Get the ship under mouse cursor
			FHitResult tHitResult;
			tPlayerController->GetHitResultUnderCursor(ECollisionChannel::ECC_GameTraceChannel2, false, tHitResult);
			ABaseShip* tTargetShip = Cast<ABaseShip>(tHitResult.GetActor());
			
			// This would have been a good instance to use an interface, IDamagable, or something along those lines.
			// Currently, this system only support BaseShips being damage, which within the scope of the project is all that
			// is required, however by using an interface I could make any object in the world be targetable.
			if (tTargetShip && tTargetShip->GetAllegiance() == EAllegiance::Enemy)
			{
				tBlackboard->SetValueAsObject("TargetShip", tTargetShip);

				ACombatShip* tOwningShip = Cast<ACombatShip>(tAIController->GetPawn());

				if (tOwningShip)
					tOwningShip->SetTargetShip(tTargetShip);
				
				return EBTNodeResult::Succeeded;
			}
		}
	}

	return EBTNodeResult::Failed;
}
