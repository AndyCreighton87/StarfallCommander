/// Enum containing all buildable types
#pragma once

#include "EBuildables.generated.h"

UENUM(BlueprintType)
enum class EBuildables : uint8
{
	Miner		UMETA(DisplayName = "Miner"),
	Fighter		UMETA(DisplayName = "Fighter"),
	Bomber		UMETA(DisplayName = "Bomber"),
	Corvette	UMETA(DisplayName = "Corvette")
};
