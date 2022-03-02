/// Struct containing information on Selectable objects for use in UI.

#pragma once
#include "UIButton.h"

#include "SelectableData.generated.h"

USTRUCT(BlueprintType)
struct FSelectableData
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Selectable Data")
	FString DisplayName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Selectable Data")
	UTexture2D* SelectionImage;
};
