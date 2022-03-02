#include "StarfallPlayerController.h"

#include "BaseShip.h"
#include "IMinable.h"
#include "Miner.h"
#include "OrderManager.h"
#include "ResourceManager.h"
#include "StarfallGameMode.h"
#include "StarfallHUD.h"
#include "UIMainWidget.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Kismet/GameplayStatics.h"

void AStarfallPlayerController::BeginPlay()
{
	Super::BeginPlay();

	// Spawn Actors
	StarfallHUD = Cast<AStarfallHUD>(GetHUD());
	UIMainWidgetRef = CreateWidget<UUIMainWidget>(this, UIWidget);
	ResourceManager = GetWorld()->SpawnActor<AResourceManager>(ResourceManagerClass);

	// Bind to GameStart Delegate
	AStarfallGameMode* tGameMode = Cast<AStarfallGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
	tGameMode->GetGameManager()->GameStartDelegate.AddDynamic(this, &AStarfallPlayerController::OnGameStart);
}

void AStarfallPlayerController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

// Set up input bindings
void AStarfallPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	
	InputComponent->BindAction("Select", IE_Pressed, this, &AStarfallPlayerController::Interact);
	InputComponent->BindAction("Select", IE_Released, this, &AStarfallPlayerController::EndSelectionDrawing);
	InputComponent->BindAction("IssueOrder", IE_Pressed, this, &AStarfallPlayerController::IssueOrder);
}

void AStarfallPlayerController::OnGameStart()
{
	ResourceManager->Init();
	InitUI();
	SetPlayerInputState(EPlayerInputStates::Standard);
}

EAllegiance AStarfallPlayerController::GetAllegiance() const
{
	return Allegiance;
}

// Show UI on screen
void AStarfallPlayerController::InitUI() const
{
	if (UIMainWidgetRef)
		UIMainWidgetRef->AddToViewport();
}

// When left mouse button clicked.
// Feedback on the next two functions would be nice as I'm pretty confident they are not optimal.
// As long as mouse cursor is not over the UI, do one of two things dependant upon input state:
// 1. Check for a Selectable under the mouse cursor. If found add to selection. Also starts the drawing
// of the selection box.
// 2. Excutes pending orders.
void AStarfallPlayerController::Interact()
{
	if(!UIMainWidgetRef->GetIsHovered())
	{
		if (InputState == EPlayerInputStates::Standard)
		{
			ClearSelection();

			FHitResult tHitResult;
			GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, false, tHitResult);
	
			if (Cast<ISelectable>(tHitResult.GetActor()))
				AddToSelection(tHitResult.GetActor());

			StarfallHUD->StartSelection();
		}
		else if (InputState == EPlayerInputStates::IssueOrder)
		{
			AStarfallGameMode* tGameMode = Cast<AStarfallGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
			tGameMode->GetOrderManager()->ExecutePendingOrders();
			SetPlayerInputState(EPlayerInputStates::Standard);
		}
	}
}

// Right mouse button clicked.
// Feedback would be nice.
// Checks what is under the mouse cursor and issues an order accordingly:
// Enemy Ship = Attack
// Mineable = Mine
// Nothing = Move
// A better approach in hindsight might have been to have an interface (IInteractable or something)
// and use an Enum to determine the type of interactable. 
void AStarfallPlayerController::IssueOrder()
{
	FHitResult tHitResult;
	GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, false, tHitResult);

	if (const auto tShip = Cast<ABaseShip>(tHitResult.GetActor()))
	{
		if (tShip->GetAllegiance() != Allegiance && tShip->GetAllegiance() != EAllegiance::Neutral)
		{
			for (const auto entry : Selection)
				entry->IssueOrder(EOrders::Attack);
		}
	}
	else if (const auto tMinable = Cast<IMinable>(tHitResult.GetActor()))
	{
		for (const auto entry : Selection)
		{
			if (Cast<AMiner>(entry.GetObject()))
				entry->IssueOrder(EOrders::Mine);
		}
	}
	else
	{
		for (const auto entry : Selection)
			entry->IssueOrder(EOrders::Move);
	}
}

// Stops the selection rectangle from being drawn on screen.
// Can't be const due to delegate
void AStarfallPlayerController::EndSelectionDrawing()
{
	if (InputState == EPlayerInputStates::Standard)
	{
		StarfallHUD->StopSelection();
		UIMainWidgetRef->UpdateUI(Selection);
	}
}

// Adds to a unit to the selection if there is room, is of the same faction and it is not already selected.
void AStarfallPlayerController::AddToSelection(TScriptInterface<ISelectable> pSelectable)
{
	if (!Selection.Contains(pSelectable) && CanAddToSelection() && pSelectable->GetAllegiance() == Allegiance)
	{
		Selection.Add(pSelectable);
		pSelectable->OnSelect();
	}
}

void AStarfallPlayerController::AddArrayToSelection(TArray<TScriptInterface<ISelectable>> pSelectables)
{
	for (const auto entry : pSelectables)
		AddToSelection(entry);
}

// Removes a unit from selection
void AStarfallPlayerController::RemoveFromSelection(TScriptInterface<ISelectable> pSelectable)
{
	if (Selection.Contains(pSelectable))
	{
		Selection.Remove(pSelectable);
		pSelectable->OnDeselect();
		UIMainWidgetRef->UpdateUI(Selection);
	}
}

void AStarfallPlayerController::RemoveArrayFromSelection(TArray<TScriptInterface<ISelectable>> pSelectables)
{
	for (auto entry : pSelectables)
	{
		if (Selection.Contains(entry))
			RemoveFromSelection(entry);
	}
}

// Cleans up the Selection and updates the UI
void AStarfallPlayerController::ClearSelection()
{
	for (const auto entry : Selection)
	{
		if (entry)
			entry->OnDeselect();
	}
	
	Selection.Empty();
	UIMainWidgetRef->ResetToStartingScreens();
	UIMainWidgetRef->ClearUI();
}

UUIMainWidget* AStarfallPlayerController::GetUIWidget()
{
	return UIMainWidgetRef;
}

AResourceManager* AStarfallPlayerController::GetResourceManager()
{
	return ResourceManager;
}
