/// A widget that represents the buttons used throughout the game. Consists of a button (that is actually invisible),
/// name and text. The functionality is handled within blueprints.

#pragma once

#include "CoreMinimal.h"
#include "IActivatable.h"
#include "Blueprint/UserWidget.h"
#include "UIButton.generated.h"

UCLASS()
class LJMUBASIC425_API UUIButton : public UUserWidget
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintReadWrite, Category = "Button")
	class UButton* Button;
	
public:

	virtual void NativeConstruct() override;
	
	UFUNCTION(BlueprintCallable, Category = "Button")
	void GetButtonReference(UButton* pButton);
	
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category="Button")
	void UpdateButtonData(const FString& pName, const UTexture2D* pImage);
	
};
