/// Widget responsible for displaying resource information such as minerals, mineral
/// tick and population.
#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ResourceWidget.generated.h"

UCLASS()
class LJMUBASIC425_API UResourceWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Resources")
	class AResourceManager* ResourceManager;

private:
	UPROPERTY()
	bool bHasBeenInitialized = false;
	
public:
	virtual void NativeConstruct() override;
	
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Resources")
	void UpdateResources(int32 pMinerals, int32 pMineralTick, int32 pPopulation, int32 pPopulationLimit);
};
