#include "SelectionInfoWidget.h"

// Add data to the selection info widget. Updates the button info, displays the button
// and then increase the index by 1.
void USelectionInfoWidget::AddToSelectionInfo(FSelectableData pSelectionData)
{
	Buttons[SelectionCount]->UpdateButtonData(pSelectionData.DisplayName, pSelectionData.SelectionImage);
	Buttons[SelectionCount]->SetVisibility(ESlateVisibility::Visible);
	SelectionCount++;
}

void USelectionInfoWidget::UpdateUI(TArray<TScriptInterface<ISelectable>> pSelectables)
{
	for (const auto entry : pSelectables)
		AddToSelectionInfo(entry->GetSelectableData());
}

// Clears all data within the Widget
void USelectionInfoWidget::ClearUI()
{
	for (const auto entry : Buttons)
		entry->SetVisibility(ESlateVisibility::Hidden);

	SelectionCount = 0;
}


