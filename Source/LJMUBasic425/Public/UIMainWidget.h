/// The UI Main Widget manages UI Elements held within it, and by extension UI Contents.
/// It passes information between the Player Controller and the many different parts of the
/// UI.
/// Any class can access this class via the Player Controller and as a result has access
/// to operations pertaining to the UI.

#pragma once

#include "CoreMinimal.h"
#include "EUIElements.h"
#include "ISelectable.h"
#include "UIContent.h"
#include "UIElementBase.h"
#include "Blueprint/UserWidget.h"
#include "UIMainWidget.generated.h"

UCLASS()
class LJMUBASIC425_API UUIMainWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	// Selection - Passed from Player Controller
	UPROPERTY()
	TArray<TScriptInterface<ISelectable>> CurrentSelection;

	// UI Contents (Poorly named, sorry)
	UPROPERTY(BlueprintReadWrite, Category = "UI Main")
	TMap<EUIContent, UUIContent*> AllScreens;

	// UI Elements
	UPROPERTY(BlueprintReadWrite, Category = "UI Main")
	TMap<EUIElements, UUIElementBase*> UIElements;

public:
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Main UI")
	void InitUI();

	UFUNCTION(BlueprintCallable, Category = "Main UI Widget")
	void LoadNewScreen(EUIContent pScreen, EUIElements pTarget);
	
	UFUNCTION()
	void UpdateUI(TArray<TScriptInterface<ISelectable>> pISelectables);
	
	UFUNCTION()
	void ClearUI() const;

	UFUNCTION()
	bool GetIsHovered();

	UFUNCTION(BlueprintCallable, Category = "Main UI Widget")
	UUIContent* GetUIScreen(EUIContent pScreen);

	UFUNCTION(BlueprintCallable, Category = "Main UI Widget")
	UUIElementBase* GetUIElement(EUIElements pElement);

	UFUNCTION()
	void ResetToStartingScreens();
};
