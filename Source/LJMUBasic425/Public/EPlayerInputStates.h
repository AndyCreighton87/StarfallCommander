/// Enum containing all Player Input States. Used by Player Controller to determine how inputs
/// should be handled.

#pragma once

#include "EPlayerInputStates.generated.h"

UENUM(BlueprintType)
enum class EPlayerInputStates : uint8
{
	Standard			UMETA(DisplayName = "Standard"),
	IssueOrder			UMETA(DisplayName = "IssueOrder"),
	UI					UMETA(DisplayName = "UI")
};
