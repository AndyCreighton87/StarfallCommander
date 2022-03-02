/// Enum containing all UI Elements. Used to show where UI Content should be placed.

#pragma once

#include "EUIElements.generated.h"

UENUM(BlueprintType)
enum class EUIElements : uint8
{
	LeftPanel		UMETA(DisplayName = "Left Panel"),
	MiddlePanel		UMETA(DisplayName = "Middle Panel"),
	RightPanel		UMETA(DisplayName = "Right Panel")
};
