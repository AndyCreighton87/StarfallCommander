/// UI Content is an abstract class. It represents a menu, or a piece of UI to be displayed on the screen.
/// It is usually displayed within a UI Element and managed through the UI Main Widget.

#pragma once

#include "CoreMinimal.h"
#include "EUIContent.h"
#include "ISelectable.h"
#include "Blueprint/UserWidget.h"
#include "UIContent.generated.h"

UCLASS()
class LJMUBASIC425_API UUIContent : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI Type")
	EUIContent UIType;
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "UI Content")
	void Init();

	UFUNCTION()
	virtual void OnFocus();

	UFUNCTION()
	virtual void EndFocus();
	
	UFUNCTION()
	virtual void UpdateUI(TArray<TScriptInterface<ISelectable>> pSelectables);
	
	//Pure virtual function
	UFUNCTION()
	virtual void ClearUI();
};
