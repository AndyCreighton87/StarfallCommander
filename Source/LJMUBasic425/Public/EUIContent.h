/// Enum containing all forms of UI Content in the game. Used to determine which screens
/// to display.

#pragma once

#include "EUIContent.generated.h"

UENUM(BlueprintType)
enum class EUIContent : uint8
{
	SelectionInfo		UMETA(DisplayName = "Selection Info"),
	BuildQueue			UMETA(DisplayName = "Build Queue"),
	OrdersButtons		UMETA(DisplayName = "Order and Ability Buttons"),
	BuildMenu			UMETA(DisplayName = "BuildMenu")
};
