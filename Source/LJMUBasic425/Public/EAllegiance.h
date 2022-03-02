/// Enum containing all possible Allegiance affiliation

#pragma once

#include "EAllegiance.generated.h"

UENUM(BlueprintType)
enum class EAllegiance : uint8
{
	Friendly	UMETA(DisplayName = "Friendly"),
	Neutral		UMETA(DisplayName = "Neutral"),
	Enemy		UMETA(DisplayName = "Enemy")
};
