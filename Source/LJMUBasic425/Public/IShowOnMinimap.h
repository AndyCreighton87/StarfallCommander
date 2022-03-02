/// Interface used on any object that needs to be shown on the minimap.
/// Currently used by Ships & Asteroids.

#pragma once

#include "CoreMinimal.h"
#include "EAllegiance.h"
#include "UObject/Interface.h"
#include "IShowOnMinimap.generated.h"

UINTERFACE(MinimalAPI)
class UShowOnMinimap : public UInterface
{
	GENERATED_BODY()
};

class LJMUBASIC425_API IShowOnMinimap
{
	GENERATED_BODY()

public:
	UFUNCTION()
	virtual EAllegiance GetAllegiance()
	{
		return {};
	}

	UFUNCTION()
	virtual void SetAllegiance(EAllegiance pAllegiance)
	{
	}
};
