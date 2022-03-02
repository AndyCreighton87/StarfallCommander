/// Widget class that displayed the end game menu. Shows whether the player has won or
/// lost and allows to returning to the main menu or exiting the game.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "EndGameMenu.generated.h"

UCLASS()
class LJMUBASIC425_API UEndGameMenu : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "End Game Menu")
	void UpdateEndGameText(const FString& pText);

	UFUNCTION()
	void ShowEndGameMenu(bool pVictory);
};
