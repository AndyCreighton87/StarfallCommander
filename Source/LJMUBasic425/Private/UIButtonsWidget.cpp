#include "UIButtonsWidget.h"

void UUIButtonsWidget::UpdateUI(TArray<TScriptInterface<ISelectable>> pSelectables)
{
	// Once I have received the selection, I store both the selectable types (ships) and
	// each activatable types (orders and abilities) in an array, using AddUnique. O(n2)
	GetUniqueSelectablesAndActivatables(pSelectables);

	// I create a map, storing the activatable types and their associated Display Name,
	// which I use as a key. This allows me to compare any activatable with the map to
	// determine its type. I also keep an array of AllActivatables. O(n)
	CreateActivatableMap();

	// To determine which buttons are to be displayed, I compare each entry in the ActivatableMap
	// with each activatable type from UniqueActivatable, keeping count of the number of matches.
	// I then compare this with the number of selectable types. This allows me to identify commonality
	// between activatables, if all types hold an activitable it is added to ButtonsToDisplayOnScreen. O(n2)
	DetermineButtonstoBeShownOnScreen();

	// I filter the activitables by comparing ButtonsToDisplayOnScreen against AllActivatables.
	// The result is ValidActivatables. I know every activatable in this list will be used in the
	// current selection. O(n2)
	FilterValidActivatables();

	// To display the buttons on screen, I have an array for each type of button, Order, Unique and Ability.
	// Each array is associated with a horizontal row in a BP Widget. 
	// I use a simple switch and Enum to determine the ability category and then update the appropiate button
	// accordingly. I also store the button and display name in a map ButtonMapForBinding. O(n)
	DisplayButtons();

	// Finally (we did it, we got there...), I use the ButtonMapForBinding and ValidActivatables to pass
	// the correct button to the correct activatables. The binding itself takes place polymorphically within
	// the IActivatable class. I don't even know the big O notation for this? O(n log n2)?? O(n3)??
	BindButtons();
}

void UUIButtonsWidget::GetUniqueSelectablesAndActivatables(TArray<TScriptInterface<ISelectable>> pSelectables)
{
	for (auto entry : pSelectables)
		UniqueSelected.AddUnique(entry);
	
	for (const auto entry : UniqueSelected)
	{
		for (auto activatable : entry->GetAllActivatables())
		{
			AllActivatables.Add(activatable);
			UniqueActivatables.AddUnique(activatable);
		}
	}
}

void UUIButtonsWidget::CreateActivatableMap()
{
	for (const auto entry : UniqueSelected)
	{
		for (auto activatable: entry->GetAllActivatables())
			ActivatableMap.Emplace(activatable->GetName(), activatable);
	}
}

void UUIButtonsWidget::DetermineButtonstoBeShownOnScreen()
{
	int tCount = 0;
	
	for (auto entry : ActivatableMap)
	{
		for(const auto activatable : UniqueActivatables)
		{
			if (activatable->GetName() == entry.Key)
				tCount++;
		}

		if (tCount == UniqueSelected.Num())
			ButtonstoDisplayOnScreen.Add(entry.Value);
		
		tCount = 0;
	}
}

void UUIButtonsWidget::FilterValidActivatables()
{
	for (const auto entry : ButtonstoDisplayOnScreen)
	{
		FString tName = entry->GetActivitableData().DisplayName;

		for (auto activatable : AllActivatables)
		{
			if (activatable->GetActivitableData().DisplayName == tName)
				ValidActivatables.Add(activatable);
		}
	}
}

void UUIButtonsWidget::DisplayButtons()
{
	for (const auto entry : ButtonstoDisplayOnScreen)
	{
		FActivitableData tData = entry->GetActivitableData();
		
		switch (tData.ActivitableType)
		{
		case EButtonType::Order:

			OrderButtons[OrderCount]->UpdateButtonData(tData.DisplayName, tData.ButtonImage);
			OrderButtons[OrderCount]->SetVisibility(ESlateVisibility::Visible);
			ButtonMapForBinding.Add(tData.DisplayName, OrderButtons[OrderCount]);
			OrderCount++;
			break;
			
		case EButtonType::UniqueOrder:
			UniqueButtons[UniqueCount]->UpdateButtonData(tData.DisplayName, tData.ButtonImage);
			UniqueButtons[UniqueCount]->SetVisibility(ESlateVisibility::Visible);
			ButtonMapForBinding.Add(tData.DisplayName, UniqueButtons[UniqueCount]);
			UniqueCount++;
			break;
		case EButtonType::Ability:
			AbilityButtons[AbilityCount]->UpdateButtonData(tData.DisplayName, tData.ButtonImage);
			AbilityButtons[AbilityCount]->SetVisibility(ESlateVisibility::Visible);
			ButtonMapForBinding.Add(tData.DisplayName, AbilityButtons[AbilityCount]);
			AbilityCount++;
			break;
		}
	}
}

void UUIButtonsWidget::BindButtons()
{
	for (const auto entry : ValidActivatables)
	{
		if (const auto tButton = *ButtonMapForBinding.Find(entry->GetActivitableData().DisplayName))
			entry->BindToButton(tButton->Button);
	}
}

void UUIButtonsWidget::ClearUI()
{
	ResetWidget();
	ClearButtonBindings();
	ClearArrays();
}

void UUIButtonsWidget::ResetWidget()
{
	// Sets all buttons to hidden and clears all counts.
	for (const auto entry : OrderButtons)
		entry->SetVisibility(ESlateVisibility::Hidden);

	for (const auto entry : UniqueButtons)
		entry->SetVisibility(ESlateVisibility::Hidden);

	for (const auto entry : AbilityButtons)
		entry->SetVisibility(ESlateVisibility::Hidden);
	
	OrderCount = 0;
	UniqueCount = 0;
	AbilityCount = 0;
}

void UUIButtonsWidget::ClearButtonBindings()
{
	for (const auto entry : AllActivatables)
		entry->RemoveBinding();
}

void UUIButtonsWidget::ClearArrays()
{
	AllActivatables.Empty();
	ButtonMapForBinding.Empty();
	UniqueSelected.Empty();
	UniqueActivatables.Empty();
	ActivatableMap.Empty();
	ButtonstoDisplayOnScreen.Empty();
	ValidActivatables.Empty();
}
