#include "EndGameMenu.h"

// Updates text based on Win/Loss
void UEndGameMenu::ShowEndGameMenu(bool pVictory)
{
	if (pVictory)
		UpdateEndGameText(TEXT("Victory!"));
	else
		UpdateEndGameText(TEXT("Game Over!"));

	AddToViewport();
}
