/// I never actually found I had a need for the GameState class, rather I handled most of state within
/// the Game Manager and Player Controller. There could be an argument that GameState could take the player of
/// Game Manager, or at least store some of the data within GameState so that it could be easily accessed by other classes.
/// However, as the Game Manager is easily obtained via the GameMode this seems irrelevant. 
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "StarfallGameState.generated.h"

UCLASS()
class LJMUBASIC425_API AStarfallGameState : public AGameStateBase
{
	GENERATED_BODY()
	
};
