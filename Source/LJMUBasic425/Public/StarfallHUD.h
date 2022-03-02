/// The HUD class used within the game. Responsible for drawing a selection
/// rectangle on the screen and feeding back any selectables to the Player Controller.
/// 
#pragma once
#include "ISelectable.h"
#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GameFramework/HUD.h"
#include "StarfallHUD.generated.h"

UCLASS()
class LJMUBASIC425_API AStarfallHUD : public AHUD
{
	GENERATED_BODY()

public:
	// The distance the mouse travels before the selection box starts drawing
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Selection Drawing")
	float StartDrawingLength = 10.0f;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Selection Drawing")
	FLinearColor SelectionRectColour = FLinearColor(0.5f, 0.0f, 0.0f, 0.5f);

	// Positions
	UPROPERTY()
	FVector2D StartPos;

	UPROPERTY()
	FVector2D CurrentPos;

	// Selection management
	UPROPERTY()
	TArray<AActor*> SelectedActors;

	UPROPERTY()
	TArray<TScriptInterface<ISelectable>>  CurrentSelection;
	
	UPROPERTY()
	TArray<TScriptInterface<ISelectable>>  Selection;
	
	UPROPERTY()
	TArray<TScriptInterface<ISelectable>>  PrevSelection;
	
	UPROPERTY()
	uint32 SelectionCount = 0;

private:
	UPROPERTY()
	bool bIsDrawing = false;
	
public:
	UFUNCTION()
	virtual void BeginPlay() override;
	
	UFUNCTION(BlueprintCallable, Category = "Selection")
	void StartSelection();

	UFUNCTION(BlueprintCallable, Category = "Selection")
	void StopSelection();

	UFUNCTION()
	virtual void DrawHUD() override;

	UFUNCTION()
	void UpdateSelection();

	UFUNCTION()
	bool IsDrawing() const;

	FORCEINLINE void CacheSelection(TArray<TScriptInterface<ISelectable>> pSelection) { CurrentSelection = Selection; }
};
