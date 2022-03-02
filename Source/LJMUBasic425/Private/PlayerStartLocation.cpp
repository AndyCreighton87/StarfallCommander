#include "PlayerStartLocation.h"

#include "Components/ArrowComponent.h"


APlayerStartLocation::APlayerStartLocation(const FObjectInitializer& ObjectInitializer)
{
	PrimaryActorTick.bCanEverTick = false;

	// Added an arrow and blank scene component allowing me to see the direction the starting location
	// is facing
	USceneComponent* tRoot = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	UArrowComponent* tArrowComponent = CreateDefaultSubobject<UArrowComponent>(TEXT("Arrow"));

	RootComponent = tRoot;
	tArrowComponent->SetupAttachment(tRoot);
}

