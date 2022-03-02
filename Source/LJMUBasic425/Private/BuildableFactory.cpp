#include "BuildableFactory.h"

ABuildableFactory::ABuildableFactory()
{
	// I needed a tick within the build queue, and this seemed to work?
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;
}

TScriptInterface<IBuildable> ABuildableFactory::CreateBuildable(FBuildableData PBuildable)
{
	return nullptr;
}
