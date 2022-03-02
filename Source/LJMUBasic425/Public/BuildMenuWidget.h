/// The Build Menu Widget class inherits from UI Content. It is responsible for displaying
/// the options for building within IBuilders (only the Capital Ship in game for the moment).

#pragma once

#include "CoreMinimal.h"
#include "BuildButton.h"
#include "BulidableData.h"
#include "IBuilder.h"
#include "UIContent.h"
#include "BuildMenuWidget.generated.h"


UCLASS()
class LJMUBASIC425_API UBuildMenuWidget : public UUIContent
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, Category = "Build Menu")
	TArray<UBuildButton*> BuildButtons;

	UPROPERTY()
	TMap<EBuildables, FBuildableData> BuildableMap;

private:
	UPROPERTY()
	int32 Index = 0;
	
	IBuilder* Builder; 

public:
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Build Menu")
	void GetButtons();
	
	UFUNCTION(BlueprintCallable, Category = "Build Menu")
	void SetButtons(TArray<FBuildableData> pBuildables, UObject* pBuilder);

	UFUNCTION(BlueprintCallable, Category = "Build Menu")
	void ExitBuildMenu();

	virtual void ClearUI() override;
private:

	UFUNCTION()
	void StartBuild(FBuildableData pBuildable);
};
