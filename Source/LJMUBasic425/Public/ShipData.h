/// Struct that holds data pertaining to Base Ship

#pragma once

#include "ShipData.generated.h"

USTRUCT(BlueprintType)
struct FShipData
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ship | Ship Data")
	float MovementSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ship | Ship Data")
	float Armour;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Ship | Ship Data")
	int32 PopulationCost;

	// Not used within the game, but remains here to allow for fog of war to be implemented
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ship | Ship Data")
	float LineOfSight;
};
