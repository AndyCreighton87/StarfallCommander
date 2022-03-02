/// The Build Queue Widget inherits from UI Content. It displays any items
/// within the build queue and progress bar of construction.
/// I had issues communicating between this and the BuildQueue itself due to
/// the use of a TQueue as previously mentioned in BuildQueue.h.
/// 
#pragma once

#include "CoreMinimal.h"
#include "BulidableData.h"
#include "UIContent.h"
#include "BuildQueueWidget.generated.h"

UCLASS()
class LJMUBASIC425_API UBuildQueueWidget : public UUIContent
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, Category = "Build Queue")
	TArray<class UUIButton*> BuildQueueIcons;

	UPROPERTY(BlueprintReadWrite, Category = "Build Queue")
	class UProgressBar* ProgressBar;

	// Default image used for when a build queue slot is empty.
	UPROPERTY(EditAnywhere, Category = "Build Queue")
	UTexture2D* BuildImage;

	UPROPERTY(BlueprintReadWrite, Category = "Build Queue")
	bool bHasBeenInitialized = false;

	UPROPERTY(EditAnywhere, Category = "Build Queue")
	float TimeToDisplayWarning = 3.0f;
	
	FTimerHandle WarningMessageTimer;

public:
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Build Queue")
	void SetupElements();
	
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Build Queue")
	void UpdateProgressBar(float pProgress);

	UFUNCTION()
	void DisplayWarning();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Build Queue")
	void ShowWarningMessage();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Build Queue")
	void HideWarningMessage();
	
	UFUNCTION()
	void Update(TArray<FBuildableData> pBuildables);

	virtual void ClearUI() override;
};
