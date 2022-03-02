/// Selection Info is a Widget that shows a visual representation of each currently
/// selected unit.

#pragma once

#include "CoreMinimal.h"
#include "ISelectable.h"
#include "UIButton.h"
#include "UIContent.h"
#include "Blueprint/UserWidget.h"
#include "SelectionInfoWidget.generated.h"

UCLASS()
class LJMUBASIC425_API USelectionInfoWidget : public UUIContent
{
	GENERATED_BODY()

public:
	// Buttons to display data onto
	UPROPERTY(BlueprintReadWrite, Category = "Selection Info")
	TArray<UUIButton*> Buttons;
	
private:
	UPROPERTY()
	int SelectionCount = 0;

public:
	UFUNCTION()
	void AddToSelectionInfo(FSelectableData pSelectionData);

	// Update the information on the buttons is handled via blueprints
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Selection Widget")
	void UpdateButton(UUIButton* pButton, int pCount);

	// Virtual functions from UI Content
	virtual void UpdateUI(TArray<TScriptInterface<ISelectable>> pSelectables) override;

	virtual void ClearUI() override;
};
