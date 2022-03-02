// Struct containing data for Combat Ships
#pragma once

#include "CombatShipData.generated.h"

USTRUCT(BlueprintType)
struct FCombatShipData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float AttackRange;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float AggroRange;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float AttackSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float AttackDamage;
};

