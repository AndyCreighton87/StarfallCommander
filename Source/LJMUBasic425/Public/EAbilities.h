// Struct containing all Abilities in game
#pragma once

#include "EAbilities.generated.h"

UENUM(BlueprintType)
enum class EAbilities : uint8
{
	RapidFire			UMETA(DisplayName = "Rapid Fire"),
	ArmBombs			UMETA(DisplayName = "Arm Bombs"),
	AllPowerToEngines	UMETA(DisplayName = "All Power To Engines"),
	ReinforceShields	UMETA(DisplayName = "Reinforce Shields"),
	GetToWorkBoys		UMETA(DisplayName = "Get To Work Boys")
};
