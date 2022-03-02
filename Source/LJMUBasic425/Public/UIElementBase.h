/// UI Element Base is an abstract class and is a container/manager for UI Content.
/// It stores a series of UI Content classes within it, and manages which are shown on
/// screen. UI Elements are themselves stored within the UI Main Widget.
///
/// There did not seem to be a Stack within Unreal that I could use, it would have been
/// perfect for this. I have emulated a stack through the use of a TArray.

#pragma once

#include "CoreMinimal.h"
#include "EUIElements.h"
#include "UIContent.h"
#include "Blueprint/UserWidget.h"
#include "UIElementBase.generated.h"

UCLASS()
class LJMUBASIC425_API UUIElementBase : public UUserWidget
{
	GENERATED_BODY()

public:
	// Where on the screen the UI Element will be displayed.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI Element")
	EUIElements Target;

	// Array of UI Content
	UPROPERTY()
	TArray<UUIContent*> Screens;

	// The current UI Content being shown
	UPROPERTY()
	UUIContent* ActiveScreen;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI Element")
	EUIContent StartingScreen;

	UPROPERTY()
	bool bMouseCurrentlyOver = false;

public:
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "UI Element")
	void InitialLoad();
	
	UFUNCTION(BlueprintCallable, Category = "UI Element")
	void AddToUI(UUIContent* pWidget);

	UFUNCTION(BlueprintCallable, Category = "UI Element")
	void RemoveFromUI(UUIContent* pWidget);

	UFUNCTION(BlueprintCallable, Category = "UI Element")
	void RemoveTopScreen();

	UFUNCTION(BlueprintCallable, Category = "UI Element")
	void ResetToStartingScreen();

	virtual void NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;

	virtual void NativeOnMouseLeave(const FPointerEvent& InMouseEvent) override;

	FORCEINLINE bool HasValidActiveScreen() const { return ActiveScreen != nullptr; }
};
