
#include "StarfallHUD.h"

#include "ISelectable.h"
#include "StarfallPlayerController.h"
#include "GameFramework/PlayerController.h"
#include "Kismet/GameplayStatics.h"

void AStarfallHUD::BeginPlay()
{
	Super::BeginPlay();
}

void AStarfallHUD::StartSelection()
{
	UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetMousePosition(StartPos.X, StartPos.Y);
	bIsDrawing = true;
}

void AStarfallHUD::StopSelection()
{
	bIsDrawing = false;
}

// Manages drawing of selection box
void AStarfallHUD::DrawHUD()
{
	Super::DrawHUD();
	
	if (bIsDrawing)
	{
		UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetMousePosition(CurrentPos.X, CurrentPos.Y);
		
		if (FVector2D::Distance(StartPos, CurrentPos) >= StartDrawingLength)
		{
			DrawRect(SelectionRectColour,StartPos.X,StartPos.Y,CurrentPos.X - StartPos.X,CurrentPos.Y - StartPos.Y);
			UpdateSelection();
		}
	}
}

// Manages the selected units
void AStarfallHUD::UpdateSelection()
{
	AStarfallPlayerController* tPlayerController = Cast<AStarfallPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));

	// Cache the previous selection
	PrevSelection = tPlayerController->GetCurrentSelection();
	tPlayerController->ClearSelection();
	SelectedActors.Empty();

	// Update found actors
	GetActorsInSelectionRectangle(StartPos, CurrentPos, SelectedActors, false);

	// Add to Player Controller Selection
	if (tPlayerController->CanAddToSelection())
	{
		for (const auto entry : SelectedActors)
		{
			if (Cast<ISelectable>(entry))
				tPlayerController->AddToSelection(entry);
		}
	}

	// Remove from selection if not found
	if (CurrentSelection != tPlayerController->GetCurrentSelection())
	{
		for (auto entry : PrevSelection)
		{
			if(!tPlayerController->GetCurrentSelection().Contains(entry))
				tPlayerController->RemoveFromSelection(entry);
		}
	}
}

bool AStarfallHUD::IsDrawing() const
{
	return bIsDrawing;
}
