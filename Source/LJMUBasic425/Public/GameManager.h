/// The Game Manager class is responsible for handing the level/game state on start and
/// end of the game. It determines the widgets to display, spawns starting ships & determines
/// win/loss conditions.

#pragma once

#include "CoreMinimal.h"
#include "BaseShip.h"
#include "GameFramework/Actor.h"
#include "GameFramework/Info.h"
#include "GameManager.generated.h"

// Delegate broadcast to inform classes of Game Starting
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FGameStart);

UCLASS()
class LJMUBASIC425_API AGameManager : public AInfo
{
	GENERATED_BODY()
	
public:	
	AGameManager();

protected:
	virtual void BeginPlay() override;

public:
	// Widget Classes
	UPROPERTY(EditAnywhere, Category = "Game Manager | Menus")
	TSubclassOf<class UUserWidget> MainMenuClass;
	
	UPROPERTY(EditAnywhere, Category = "Game Manager | Menus")
	TSubclassOf<class UUserWidget> EndGameMenuClass;

	// Delegates
	UPROPERTY()
	FGameStart GameStartDelegate;
	
private:
	// Widgets
	UPROPERTY()
	class UMainMenu* MainMenu;

	UPROPERTY()
	class UEndGameMenu* EndGameMenu;

	// Capital Ships
	UPROPERTY(EditAnywhere, Category = "Capital Ships")
	TSubclassOf<ABaseShip> FriendlyCapitalShipClass;

	UPROPERTY()
	ABaseShip* FriendlyCapitalShip;

	UPROPERTY(EditAnywhere, Category = "Capital Ships")
	TSubclassOf<ABaseShip> EnemyCapitalShipClass;
	
	UPROPERTY()
	ABaseShip* EnemyCapitalShip;

	// The starting location for the StarfallCamera (default pawn)
	UPROPERTY()
	FVector CameraStartPos;
	
public:
	UFUNCTION(BlueprintCallable, Category = "Game Manager")
	void OnStartGame();

	UFUNCTION()
	ABaseShip* GetCapitalShip(EAllegiance pAllegiance) const;

	UFUNCTION(BlueprintCallable, Category = "Game Manager")
	void ShowMainMenu();

private:
	UFUNCTION()
	void SpawnCapitalShip(class APlayerStartLocation* pStartLocation);

	UFUNCTION()
	void OnCapitalShipDeath(ABaseShip* pShip);

	UFUNCTION()
	void EndGame(bool pVictory);
	
	UFUNCTION()
	void CleanupWorld() const;
};
