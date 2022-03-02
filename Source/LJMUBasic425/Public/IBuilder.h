/// Interface for anything that can build other units. Includes functions for fetching the BuildQueue and
/// array of buildables. Currently used within Capital Ship.

#pragma once

#include "CoreMinimal.h"
#include "BulidableData.h"
#include "UObject/Interface.h"
#include "IBuilder.generated.h"

UINTERFACE(meta = (CannotImplementInterfaceInBlueprint))
class UBuilder : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class LJMUBASIC425_API IBuilder
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION(BlueprintCallable, Category = "Builder")
	virtual TArray<FBuildableData> GetBuildables()
	{
		return {};
	}

	UFUNCTION(BlueprintCallable, Category = "Builder")
	virtual class ABuildQueue* GetBuildQueue()
	{
		return{};
	}

	UFUNCTION()
	virtual FVector GetRallyPointPos()
	{
		return {};
	}
};
