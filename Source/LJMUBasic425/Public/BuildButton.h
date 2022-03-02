/// Subclass of UI Button. Designed to store information pertaining to IBuildables for
/// use in the Build Menu.
/// I had a strange issue with this class, in that I needed to pass a variable with the buttons
/// OnClicked event, the ship that was to be built (found in FBuildableData). However, OnClicked
/// did not seem to offer this, to get around this I had OnClicked trigger another delegate,
/// FBuildButtonPressed, which could pass the data needed.

#pragma once

#include "CoreMinimal.h"
#include "BulidableData.h"
#include "EBuildables.h"
#include "UIButton.h"
#include "BuildButton.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FBuildButtonPressed, FBuildableData, BuildableData);

UCLASS()
class LJMUBASIC425_API UBuildButton : public UUIButton
{
	GENERATED_BODY()

public:
	FBuildButtonPressed BuildButtonDelegate;

private:
	FBuildableData Buildable;

public:
	UFUNCTION()
	FBuildableData GetBuildable() const;

	UFUNCTION()
	void SetBuildable(FBuildableData pBuildable);

	UFUNCTION()
	void BindButton();

	UFUNCTION()
	void RemoveBinding() const;

private:
	UFUNCTION()
	void OnBuildButtonPressed();
};
