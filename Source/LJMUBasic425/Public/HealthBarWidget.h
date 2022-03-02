/// Widget used to represent a ships health bar. Used by HealthBarComponent.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HealthBarWidget.generated.h"

UCLASS()
class LJMUBASIC425_API UHealthBarWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	// Set the percentage of the health bar. Via Blueprints.
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Health Bar")
	void UpdateHealthBar(float pAmount);
};
