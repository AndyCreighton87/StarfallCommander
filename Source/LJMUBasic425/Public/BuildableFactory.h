// An abstract factory that creates Buildables. Used by the BuildQueue.

#pragma once

#include "CoreMinimal.h"
#include "BulidableData.h"
#include "IBuildable.h"
#include "EBuildables.h"
#include "Factories/Factory.h"
#include "GameFramework/Info.h"
#include "BuildableFactory.generated.h"

UCLASS(Abstract)
class LJMUBASIC425_API ABuildableFactory : public AInfo
{
	GENERATED_BODY()
public:
	ABuildableFactory();

public:
	virtual TScriptInterface<IBuildable> CreateBuildable(FBuildableData PBuildable);
};
