/// Interface for anything in the game that can be activated. Designed for use with Orders & Abilities but
/// could be expanded anything. Includes functions for binding buttons.

#pragma once

#include "CoreMinimal.h"
#include "ActivitableData.h"
#include "UObject/Interface.h"
#include "IActivatable.generated.h"

// Forward declarations

class UButton;
class UUIButton;

// Cannot Implement In Blueprint so it can be called via BPs
UINTERFACE(meta = (CannotImplementInterfaceInBlueprint))
class UActivatable : public UInterface
{
	GENERATED_BODY()
};

class LJMUBASIC425_API IActivatable
{
	GENERATED_BODY()
	
public:
	UFUNCTION()
	virtual void OnActivate()
	{
	}

	UFUNCTION(BlueprintCallable, Category = "Activatable")
	virtual FActivitableData GetActivitableData()
	{
		return {};
	}

	UFUNCTION()
	virtual FString GetName()
	{
		return {};
	}

	UFUNCTION()
	virtual TArray<FString> GetActivitableNames()
	{
		return {};
	}

	UFUNCTION()
	virtual void BindToButton(UButton* pButton)
	{
	}
	
	UFUNCTION()
	virtual void RemoveBinding()
	{
	}

	UFUNCTION()
	virtual bool GetRequiresInput()
	{
		return false;
	}
};
