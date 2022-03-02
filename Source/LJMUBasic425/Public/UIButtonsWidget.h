/// <summary>
/// 
/// The purpose of this class is to display buttons relevant to the current selection.
/// Each button shown must be an order or ability (activatable) owned by ALL ships (selectable)
/// before it is displayed. (If one ship dose not have an order, no ships have that order).
///
/// This was by far the most challenging task as of yet, and I predict of the entire project.
/// I understand the code is not perfect, it is most likely unnecessarily convoluted and there is a lot of O(n2).
/// But at this point I have to proceed with the remainder of the coursework. The in-game effect is nice, but
/// I believe it could be much more optimal. I have provided a breakdown of the process in the UpdateUI method.
/// I have attempted to be as literal as possible with naming conventions in the hope that it will
/// be even slightly clearer to whomever marks this.
///
/// If I were to receive any feedback on this coursework, I would greatly appreciate it if this class
/// in particular were included.
/// </summary>

#pragma once

#include "CoreMinimal.h"
#include "IActivatable.h"
#include "UIButton.h"
#include "UIContent.h"
#include "Blueprint/UserWidget.h"
#include "UIButtonsWidget.generated.h"

UCLASS()
class LJMUBASIC425_API UUIButtonsWidget : public UUIContent
{
	GENERATED_BODY()

public:
	// Buttons
	UPROPERTY(BlueprintReadWrite, Category = "Buttons")
	TArray<UUIButton*> OrderButtons;

	UPROPERTY(BlueprintReadWrite, Category = "Buttons")
	TArray<UUIButton*> UniqueButtons;

	UPROPERTY(BlueprintReadWrite, Category = "Buttons")
	TArray<UUIButton*> AbilityButtons;

	UPROPERTY()
	class AOrderManager* OrderManager;
	
private:
	// Data Structures
    UPROPERTY()
    TMap<FString, UUIButton*> ButtonMapForBinding;

	UPROPERTY()
	TArray<TScriptInterface<IActivatable>> AllActivatables;

	UPROPERTY()
	TArray<TScriptInterface<ISelectable>> UniqueSelected;

	UPROPERTY()
	TArray<TScriptInterface<IActivatable>> UniqueActivatables;

	UPROPERTY()
	TMap<FString, TScriptInterface<IActivatable>> ActivatableMap;

	UPROPERTY()
	TArray<TScriptInterface<IActivatable>> ButtonstoDisplayOnScreen;

	UPROPERTY()
	TArray<TScriptInterface<IActivatable>> ValidActivatables;

	// Counters
	UPROPERTY()
	int32 OrderCount = 0;

	UPROPERTY()
	int32 UniqueCount = 0;

	UPROPERTY()
	int32 AbilityCount = 0;

	UPROPERTY()
	int32 NumSelected;

public:
	// Virtual functions inherited from UI Content
	virtual void UpdateUI(TArray<TScriptInterface<ISelectable>> pSelectables) override;

	virtual void ClearUI() override;

private:
	UFUNCTION()
	void GetUniqueSelectablesAndActivatables(TArray<TScriptInterface<ISelectable>> pSelectables);

	UFUNCTION()
	void CreateActivatableMap();

	UFUNCTION()
	void DetermineButtonstoBeShownOnScreen();
	
	UFUNCTION()
	void FilterValidActivatables();

	UFUNCTION()
	void DisplayButtons();

	UFUNCTION()
	void BindButtons();

	UFUNCTION()
	void ResetWidget();
	
	UFUNCTION()
	void ClearButtonBindings();

	UFUNCTION()
	void ClearArrays();
};
