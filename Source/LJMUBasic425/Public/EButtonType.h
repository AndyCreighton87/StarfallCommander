/// Enum containing all Activatable Button Types. Used by UIButtonsWidget
#pragma once

#include "EButtonType.generated.h"

UENUM(BlueprintType)
enum class EButtonType : uint8
{
	Order			UMETA(DisplayName = "Order"),
	UniqueOrder		UMETA(DisplayName = "Unique Order"),
	Ability			UMETA(DisplaName = "Ability")
};
