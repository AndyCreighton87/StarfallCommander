#include "MinimapWidget.h"

#include "EngineUtils.h"
#include "IShowOnMinimap.h"
#include "StarfallCamera.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"

void UMinimapWidget::NativeConstruct()
{
	Super::NativeConstruct();

}

void UMinimapWidget::InitMinimap_Implementation()
{
	// Set up colours
	ColourMap.Add(EAllegiance::Friendly, FriendlyColour);
	ColourMap.Add(EAllegiance::Neutral, NeutralColour);
	ColourMap.Add(EAllegiance::Enemy, EnemyColour);

	// Get a reference to the camera
	for (TActorIterator<AStarfallCamera> ActorItr(GetWorld()); ActorItr; ++ActorItr)
		Camera = Cast<AStarfallCamera>(*ActorItr);

	// Set a custom tick for the minimap (to reduce the performance hit)
	constexpr float tCustomTickTimeStep = 0.1f;
	FTimerDelegate tTimerDelegate;
	tTimerDelegate.BindLambda([this]
	{
		MinimapTick();
	});
	
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, tTimerDelegate, tCustomTickTimeStep, true);
}

// Update the Actors to be shown on the minimap. Gets all actors that implement IShowOnMinimap
// and will get an icon from the pool if that actor does not already exist.
// This may have been bettered managed through the use of delegates (similar to how removing
// icons is handled), however as it currently stands it's a nice catch-all.
void UMinimapWidget::UpdateActors()
{
	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsWithInterface(GetWorld(), UShowOnMinimap::StaticClass(), FoundActors);

	ArrayOfActors = FoundActors;
	for (const auto entry : FoundActors)
	{
		if (!MinimapIconMap.Contains(entry))
		{
			// Bind to the OnDestroyed delegate to remove the minimap icon
			entry->OnDestroyed.AddDynamic(this, &UMinimapWidget::AddBackToPool);
			MinimapIconMap.Add(entry, GetNextInPool(entry));
		}
	}
}

// Translates the minimap icon within the widget space based upon the Actors world position
// based upon the level bounds.
void UMinimapWidget::UpdatePositions()
{
	for (const auto entry : MinimapIconMap)
	{
		FVector2D tActorPos = FVector2D(entry.Key->GetActorLocation().X, entry.Key->GetActorLocation().Y * -1.0f);
		FVector2D tPos = tActorPos / (LevelSize / MinimapSize);
		const float tAngle = FindAngle(FVector2D(0.0f, 0.0f), tActorPos);
		const FVector2D tCoords = FindCoords(tPos.Size(), tAngle);
		entry.Value->SetRenderTranslation(tCoords);
	}
}

// Manages the camera icon, so that it will move in sync with the camera
void UMinimapWidget::UpdateCameraIcon() const
{
	if (MinimapCameraIcon)
	{
		FVector2D tActorPos = FVector2D(Camera->GetActorLocation().X, Camera->GetActorLocation().Y * - 1.0f);
		FVector2D tPos = tActorPos / (LevelSize / MinimapSize);
		const float tAngle = FindAngle(FVector2D(0.0f, 0.0f), tActorPos);
		const FVector2D tCoords = FindCoords(tPos.Size(), tAngle);
		MinimapCameraIcon->SetRenderTranslation(tCoords);
	}
}

float UMinimapWidget::FindAngle(FVector2D pFirstPoint, FVector2D pSecondPoint)
{
	const float tAdj = pFirstPoint.X - pSecondPoint.X;
	const float tOpp = pFirstPoint.Y - pSecondPoint.Y;
	return UKismetMathLibrary::Atan2(tOpp, tAdj);
}

FVector2D UMinimapWidget::FindCoords(float pRadius, float pAngle)
{
	float tXCoord = FMath::Sin(pAngle);
	tXCoord *= pRadius;

	float tYCoord = FMath::Cos(pAngle);
	tYCoord *= pRadius;

	return FVector2D(tXCoord, tYCoord);
}

void UMinimapWidget::MinimapTick()
{
	UpdateActors();
	UpdatePositions();
	UpdateCameraIcon();
}

// Returns a minimap icon from the pool.
UMinimapIcon* UMinimapWidget::GetNextInPool(AActor* pActor)
{
	UMinimapIcon* tIcon = MinimapIconPool[PoolCount];
	IShowOnMinimap* tObject = Cast<IShowOnMinimap>(pActor);
	
	for (const auto entry : ColourMap)
	{
		if (entry.Key == tObject->GetAllegiance())
			tIcon->SetColorAndOpacity(entry.Value);
	}
	tIcon->SetVisibility(ESlateVisibility::Visible);
	PoolCount++;
	return tIcon;
}

// Adds an icon back to the pool
void UMinimapWidget::AddBackToPool(AActor* pActor)
{
	const auto tIcon = MinimapIconMap.FindAndRemoveChecked(pActor);
	pActor->OnDestroyed.RemoveAll(this);
	tIcon->SetVisibility(ESlateVisibility::Hidden);
	PoolCount--;
}
