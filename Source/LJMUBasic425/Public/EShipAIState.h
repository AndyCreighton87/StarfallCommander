/// Enum containing all AI states within the game for ships.
/// This was a strange one, due to Behaviour Tree requiring a Blueprint Enum
/// opposed to a C++ one, I had to create a BP version of this, ensuring the entries
/// matched. Likely not optimal, however it functions well. Could present issues when/if
/// additional AI States were added (they would need to be added in both places).

#pragma once

#include "EShipAIState.generated.h"

UENUM(BlueprintType)
enum class EShipAIState : uint8
{
	Idle		UMETA(DisplayName = "Idle"),
	Move		UMETA(DisplayName = "Move"),
	Attack		UMETA(DisplayName = "Attack"),
	Mine		UMETA(DisplayName = "Mine"),
	OnSpawn		UMETA(DisplayName = "On Spawn")
};
