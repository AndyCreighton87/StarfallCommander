/// Miner inherits from Non Combat Ship. Is responsible for providing basic functionality of
/// the miner ship. Achieves this through Begin/End Overlap of the BoxCollider component.
/// Increase or decreases the mineral tick rate accordingly.

#pragma once

#include "CoreMinimal.h"
#include "NonCombatShip.h"


#include "Miner.generated.h"

UCLASS()
class LJMUBASIC425_API AMiner : public ANonCombatShip
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(HideInDetailPanel))
	int32 Damage;
};
