/// Enum containing all Order types

#pragma once

#include "EOrders.generated.h"

UENUM(BlueprintType)
enum class EOrders : uint8
{
	Stop		UMETA(DisplayName = "Stop Order"),
	Move		UMETA(DisplayName = "Move Order"),
	Attack		UMETA(DisplayName = "Attack Order"),
	Mine		UMETA(DisplayName = "Mine Order")
};
