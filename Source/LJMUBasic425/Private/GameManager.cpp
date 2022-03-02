#include "GameManager.h"

#include "BuildQueue.h"
#include "CapitalShip.h"
#include "CapitalShipEnemy.h"
#include "EndGameMenu.h"
#include "EngineUtils.h"
#include "EShipAIState.h"
#include "MainMenu.h"
#include "PlayerStartLocation.h"
#include "StarfallCamera.h"
#include "StarfallPlayerController.h"
#include "UIMainWidget.h"
#include "WeaponEffect.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Blueprint/UserWidget.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include "Kismet/GameplayStatics.h"

AGameManager::AGameManager()
{
	PrimaryActorTick.bCanEverTick = false;
}

void AGameManager::BeginPlay()
{
	Super::BeginPlay();

	// Set initial player input state
	AStarfallPlayerController*  tPlayerController = Cast<AStarfallPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	tPlayerController->SetPlayerInputState(EPlayerInputStates::UI);

	// Init Main Menu
	MainMenu = Cast<UMainMenu>(CreateWidget<UUserWidget>(tPlayerController, MainMenuClass));
	MainMenu->AddToViewport();

	// Init End Game Menu
	EndGameMenu = Cast<UEndGameMenu>(CreateWidget<UUserWidget>(tPlayerController, EndGameMenuClass));
}

void AGameManager::OnStartGame()
{
	// Hide Main Menu
	MainMenu->RemoveFromViewport();
	
	GameStartDelegate.Broadcast();
	
	// Spawn a Capital Ship in each starting location
	for(TActorIterator<APlayerStartLocation> ActorItr(GetWorld()); ActorItr; ++ActorItr)
		SpawnCapitalShip(*ActorItr);

	// Set camera position
	const APlayerController* tPlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	tPlayerController->GetPawn()->SetActorLocation(CameraStartPos);
}

// Returns the capital ship of a given allegiance.
// If the game were to be expanded this would need additional work to allow for more than 1
// capital ship (what if there were 10 different enemies?).
ABaseShip* AGameManager::GetCapitalShip(EAllegiance pAllegiance) const
{
	ABaseShip* tShip;
	
	switch(pAllegiance)
	{
		case EAllegiance::Friendly:
			tShip = FriendlyCapitalShip;
			break;
		
		case EAllegiance::Enemy:
			tShip = EnemyCapitalShip;
			break;
		
		default:
			tShip = nullptr;
	}

	return tShip;
}

// Removes all other widgets and shows the Main Menu
void AGameManager::ShowMainMenu()
{
	UWidgetLayoutLibrary::RemoveAllWidgets(this);
	MainMenu->AddToViewport();
}

// Spawns Capital Ship in each starting location
void AGameManager::SpawnCapitalShip(APlayerStartLocation* pStartLocation)
{
	// The type of capital ship spawned is tied to the Allegiance of the PlayerStartLocation.
	// This allows for the placement of spawn locations in the world, with the faction of the
	// spawned ship easily modified through the details panel. If we wanted more than one capital
	// ship for a level, it's simply a case of dragging another start location into the world.

	// I have used a simple switch as I know for the scope of this project I will only ever have
	// exactly 2 Allegiances that can spawn Capital Ships: Friendly and Enemy.
	// If the scope of the game was to be extended to allow for additional players and factions, an
	// abstract factory could be implemented.
	
	const FVector tPos = pStartLocation->GetActorLocation();
	const FRotator tRot = pStartLocation->GetActorRotation();
	const FActorSpawnParameters tActorSpawnParams;

	switch (pStartLocation->Allegiance)
	{
		case EAllegiance::Friendly:
			FriendlyCapitalShip = GetWorld()->SpawnActor<ABaseShip>(FriendlyCapitalShipClass, tPos, tRot, tActorSpawnParams);
			FriendlyCapitalShip->ShipDeathDelegate.AddDynamic(this, &AGameManager::OnCapitalShipDeath);
			CameraStartPos = tPos;
			break;
		case EAllegiance::Enemy:
			EnemyCapitalShip = GetWorld()->SpawnActor<ABaseShip>(EnemyCapitalShipClass, tPos, tRot, tActorSpawnParams);
			EnemyCapitalShip->ShipDeathDelegate.AddDynamic(this, &AGameManager::OnCapitalShipDeath);
			break;
		default:
			break;
	}
}

// Determine Win/Loss
void AGameManager::OnCapitalShipDeath(ABaseShip* pShip)
{
	if (pShip == FriendlyCapitalShip)
		EndGame(false);
	else if (pShip == EnemyCapitalShip)
		EndGame(true);
}

void AGameManager::EndGame(bool pVictory)
{
	// Set UI input state & show End Game Menu
	AStarfallPlayerController* tPlayerController = Cast<AStarfallPlayerController>(UGameplayStatics::GetPlayerController(this, 0));
	tPlayerController->SetPlayerInputState(EPlayerInputStates::UI);
	EndGameMenu->ShowEndGameMenu(pVictory);

	// Get rid of all remaining actors
	CleanupWorld();
}

// Destroy all remaining actors in the scene + other tasks that need completed before starting
// a new game.
void AGameManager::CleanupWorld() const
{
	// Clear up Capital Ship timers & Build Queue
	Cast<ACapitalShipEnemy>(EnemyCapitalShip)->CleanUp();
	Cast<ACapitalShip>(FriendlyCapitalShip)->CleanUp();
	
	// Destroy all base ships
	for (TActorIterator<ABaseShip> ActorItr(GetWorld()); ActorItr; ++ActorItr)
		ActorItr->Destroy();

	// Destroy all orders & abilities
	TArray<AActor*> tActivtables;
	UGameplayStatics::GetAllActorsWithInterface(GetWorld(), UActivatable::StaticClass(), tActivtables);
	for (const auto entry : tActivtables)
		entry->Destroy();

	// Destroy all projectiles
	for (TActorIterator<AWeaponEffect> ActorItr(GetWorld()); ActorItr; ++ActorItr)
		ActorItr->Destroy();

	//Clear any data from UI
	AStarfallPlayerController* tPlayerController = Cast<AStarfallPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	tPlayerController->GetUIWidget()->ClearUI();
	
}

