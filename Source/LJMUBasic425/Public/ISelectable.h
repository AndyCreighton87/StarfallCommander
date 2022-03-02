// Interface designed for anything in the game that can be selected. Currently restricted to ships
// but anything in theory could be selected.

#pragma once

#include "CoreMinimal.h"
#include "EAllegiance.h"
#include "EOrders.h"
#include "IActivatable.h"
#include "SelectableData.h"
#include "UObject/Interface.h"
#include "ISelectable.generated.h"

UINTERFACE(MinimalAPI)
class USelectable : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class LJMUBASIC425_API ISelectable
{
	GENERATED_BODY()

public:
	UFUNCTION()
	virtual void OnSelect()
	{
	}

	UFUNCTION()
	virtual void OnDeselect()
	{
	}

	UFUNCTION()
	virtual FSelectableData GetSelectableData()
	{
		return {};
	}

	UFUNCTION()
	virtual TArray<TScriptInterface<IActivatable>> GetAllActivatables()
	{
		return {};
	}

	UFUNCTION()
	virtual void IssueOrder(EOrders pOrder)
	{
	}

	UFUNCTION()
	virtual EAllegiance GetAllegiance()
	{
		return {};
	}
};
