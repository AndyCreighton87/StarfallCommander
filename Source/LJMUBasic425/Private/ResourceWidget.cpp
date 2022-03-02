#include "ResourceWidget.h"
#include "ResourceManager.h"
#include "StarfallPlayerController.h"
#include "Kismet/GameplayStatics.h"

void UResourceWidget::NativeConstruct()
{
	Super::NativeConstruct();

	// Get a reference to the resource manager and setup a delegate to UpdateResources
	AStarfallPlayerController* tPlayerController = Cast<AStarfallPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	ResourceManager = tPlayerController->GetResourceManager();
	
	if (ResourceManager && !bHasBeenInitialized)
	{
		ResourceManager->ResourcesUpdatedDelegate.AddDynamic(this, &UResourceWidget::UpdateResources);
		bHasBeenInitialized = true;
	}
}
