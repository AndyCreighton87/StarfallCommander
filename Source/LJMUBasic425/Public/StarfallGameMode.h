/// The custom Game Mode used throughout the game. Contains a reference to the Order Manager
/// and Game Manager. The Game manager has been spawned with TSubClassOf to allow for different
/// Game Managers with different Win/Loss conditions.

#pragma once

#include "CoreMinimal.h"
#include "GameManager.h"
#include "GameFramework/GameModeBase.h"
#include "StarfallGameMode.generated.h"

/**
 * 
 */
UCLASS()
class LJMUBASIC425_API AStarfallGameMode : public AGameModeBase
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaSeconds) override;

private:
	UPROPERTY()
	class AOrderManager* OrderManager;

	UPROPERTY(EditAnywhere, Category = "Starfall Game Mode")
	TSubclassOf<AGameManager> GameManagerClass;
	
	UPROPERTY()
	AGameManager* GameManager;

public:
	virtual void InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage) override;

	virtual FString InitNewPlayer(APlayerController* NewPlayerController, const FUniqueNetIdRepl& UniqueId, const FString& Options, const FString& Portal) override;

	virtual void PreInitializeComponents() override;

	virtual void SetPlayerDefaults(APawn* PlayerPawn) override;

	virtual void InitGameState() override;

	UFUNCTION(BlueprintCallable, Category = "Starfall Game Mode")
	AOrderManager* GetOrderManager();

	UFUNCTION(BlueprintCallable, Category = "Starfall Game Mode")
	AGameManager* GetGameManager();
	
};
