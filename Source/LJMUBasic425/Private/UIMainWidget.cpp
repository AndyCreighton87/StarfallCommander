#include "UIMainWidget.h"
#include "BaseShip.h"
#include "SelectionInfoWidget.h"
#include "UIElementBase.h"

// Update all UI Element active screens based upon the current selection
void UUIMainWidget::UpdateUI(TArray<TScriptInterface<ISelectable>> pISelectables)
{
	ClearUI();
	
	for (const auto target : UIElements)
		if(target.Value->HasValidActiveScreen())
			target.Value->ActiveScreen->UpdateUI(pISelectables);
}

// Loads a new UI Content to a target UI Element
void UUIMainWidget::LoadNewScreen(EUIContent pScreen, EUIElements pTarget)
{
	UUIElementBase* tUIElement = *UIElements.Find(pTarget);
	if (*AllScreens.Find(pScreen))
		tUIElement->AddToUI(*AllScreens.Find(pScreen));
}

// Clears all active screens
void UUIMainWidget::ClearUI() const
{
	for (const auto entry : UIElements)
		if(entry.Value->HasValidActiveScreen())
			entry.Value->ActiveScreen->ClearUI();
}

// Determines if the mouse cursor is over the UI. Stops selection clicks from
// happening when clicking buttons.
bool UUIMainWidget::GetIsHovered()
{
	for (const auto entry : UIElements)
	{
		if(entry.Value->bMouseCurrentlyOver)
			return true;
	}
	return false;
}

// Returns a UI Content
UUIContent* UUIMainWidget::GetUIScreen(EUIContent pScreen)
{
	for (const auto entry : AllScreens)
	{
		if (entry.Key == pScreen)
			return entry.Value;
	}

	return nullptr;
}

// Returns a UI Element
UUIElementBase* UUIMainWidget::GetUIElement(EUIElements pElement)
{
	for (const auto entry : UIElements)
	{
		if (entry.Key == pElement)
			return entry.Value;
	}

	return nullptr;
}

void UUIMainWidget::ResetToStartingScreens()
{
	for (auto entry : UIElements)
		entry.Value->ResetToStartingScreen();
}
