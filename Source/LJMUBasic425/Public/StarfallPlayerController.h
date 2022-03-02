/// The Player Controller class used throughout the game. Manages player input
/// and the selection information. Selection information could have been abstracted and
/// time permitting it would have been.
/// Also keeps a reference to the UI Main Widget. The idea being that each Player Controller
/// would have their own UI specific to them.

#pragma once

#include "EPlayerInputStates.h"
#include "CoreMinimal.h"
#include "EAllegiance.h"
#include "ISelectable.h"
#include "GameFramework/PlayerController.h"
#include "StarfallPlayerController.generated.h"

UCLASS()
class LJMUBASIC425_API AStarfallPlayerController : public APlayerController
{
	GENERATED_BODY()
	
protected:
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaSeconds) override;

public:
	// Selection variables
	UPROPERTY(EditAnywhere, Category = "Selection")
	int MaxSelectionSize = 20;

	UPROPERTY()
	int CurrentSelectionSize = 0;
	
private:
	// The players Allegiance
	UPROPERTY(VisibleAnywhere, Category = "Alligence")
	EAllegiance Allegiance;

	// Selection
	UPROPERTY()
	TArray<TScriptInterface<ISelectable>> Selection;

	// HUD
	UPROPERTY()
	class AStarfallHUD* StarfallHUD;

	// The current input state
	UPROPERTY()
	EPlayerInputStates InputState;
	
	// Resource Manager and UI Main Widget use TSubClassOf to allow for future extension.
	UPROPERTY(EditAnywhere, Category = "Resources")
	TSubclassOf<class AResourceManager> ResourceManagerClass;
	
	UPROPERTY()
	AResourceManager* ResourceManager;

	UPROPERTY(EditAnywhere, Category = "UI")
	TSubclassOf<class UUIMainWidget> UIWidget;

	UPROPERTY()
	UUIMainWidget* UIMainWidgetRef;

public:
	UFUNCTION()
	void OnGameStart();
	
	UFUNCTION(BlueprintGetter, Category = "Player")
	EAllegiance GetAllegiance() const;

	UFUNCTION()
	void InitUI() const;
	
	UFUNCTION(BlueprintCallable, Category = "Player | Selection")
	void AddToSelection(TScriptInterface<ISelectable> pSelectable);
	
	UFUNCTION(BlueprintCallable, Category = "Player | Selection")
	void AddArrayToSelection(TArray<TScriptInterface<ISelectable>> pSelectables);

	UFUNCTION(BlueprintCallable, Category = "Player | Selection")
	void RemoveFromSelection(TScriptInterface<ISelectable> pSelectable);
	
	UFUNCTION(BlueprintCallable, Category = "Player | Selection")
	void RemoveArrayFromSelection(TArray<TScriptInterface<ISelectable>> pSelectables);

	UFUNCTION(BlueprintCallable, Category = "Player | Selection")
	void ClearSelection();

	UFUNCTION(BlueprintCallable, Category ="Player | UI")
	UUIMainWidget* GetUIWidget();

	UFUNCTION(BlueprintCallable, Category = "Player | Resources")
	AResourceManager* GetResourceManager();

	FORCEINLINE void SetPlayerInputState(EPlayerInputStates pState) { InputState = pState; }

	FORCEINLINE bool CanAddToSelection() const { return Selection.Num() < MaxSelectionSize; }

	FORCEINLINE TArray<TScriptInterface<ISelectable>> GetCurrentSelection() const { return Selection; };

	FORCEINLINE int32 GetNumberSelected() const { return Selection.Num(); }

private:
	UFUNCTION()
	void EndSelectionDrawing();
	
	UFUNCTION()
	void Interact();

	UFUNCTION()
	void IssueOrder();
	
	virtual void SetupInputComponent() override;
};
