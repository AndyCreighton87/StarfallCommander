// Struct that holds Type & UI data for use with classes that inherit from IActivatable

#pragma once
#include "EButtonType.h"

#include "ActivitableData.generated.h"

USTRUCT(BlueprintType)
struct FActivitableData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Selectable Data");
	EButtonType ActivitableType;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Selectable Data")
	FString DisplayName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Selectable Data")
	UTexture2D* ButtonImage;
};
