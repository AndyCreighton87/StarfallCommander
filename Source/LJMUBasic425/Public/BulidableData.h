/// Struct that holds data for Buildables. Used within the Build Queue and Build Menu
/// 
#pragma once
#include "BaseShip.h"
#include "EBuildables.h"

#include "BulidableData.generated.h"

USTRUCT(BlueprintType)
struct FBuildableData
{
  GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Buildable Data")
	UTexture2D* DisplayImage;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Buildable Data")
	FString DisplayName;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Buildable Data")
	int32 MineralCost;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Buildable Data")
	int32 PopulationCost;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Buildable Data")
	float BuildTime;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Buildable Data")
	EBuildables Type;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Buildable Data")
	float StartingHeight;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Buildable Data")
	TSubclassOf<ABaseShip> BuildableClass;
};
