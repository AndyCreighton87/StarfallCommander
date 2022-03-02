#include "UIElementBase.h"

// Adds a new UI Content to the Element and sets it to active
void UUIElementBase::AddToUI(UUIContent* pWidget)
{
	for (const auto entry : Screens)
		entry->SetVisibility(ESlateVisibility::Hidden);;

	Screens.Add(pWidget);
	ActiveScreen = pWidget;
	ActiveScreen->SetVisibility(ESlateVisibility::Visible);
}

// Removes an element from the UI. Sets the Active Screen to be the last entry
// in Screens
void UUIElementBase::RemoveFromUI(UUIContent* pWidget)
{
	const int32 tIndex = Screens.Find(pWidget);
	Screens[tIndex]->SetVisibility(ESlateVisibility::Hidden);
	Screens.RemoveAt(tIndex);
	
	ActiveScreen = Screens.Last();
	ActiveScreen->SetVisibility(ESlateVisibility::Visible);
	ActiveScreen->OnFocus();
}

// Removes the top screen from view
void UUIElementBase::RemoveTopScreen()
{
	//This needs more work
	const int32 tIndex = Screens.Num() - 1;
	Screens[tIndex]->SetVisibility(ESlateVisibility::Hidden);
	Screens[tIndex]->ClearUI();
	Screens.RemoveAt(tIndex);
	
	ActiveScreen = Screens.Last();
	ActiveScreen->SetVisibility(ESlateVisibility::Visible);
}

// Sets the screen back to the original starting screen
void UUIElementBase::ResetToStartingScreen()
{
	if (ActiveScreen->UIType != StartingScreen)
		RemoveTopScreen();
}

// Manages if the mouse is over the UI. Used within Player Controller.
void UUIElementBase::NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	if(!InMouseEvent.IsMouseButtonDown(EKeys::LeftMouseButton))
		bMouseCurrentlyOver = true;
}

void UUIElementBase::NativeOnMouseLeave(const FPointerEvent& InMouseEvent)
{
	if(!InMouseEvent.IsMouseButtonDown(EKeys::LeftMouseButton))
		bMouseCurrentlyOver = false;
}
