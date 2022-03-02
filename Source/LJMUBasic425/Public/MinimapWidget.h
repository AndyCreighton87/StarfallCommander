/// Inherits from UI Content. The widget that represents the minimap.
/// There are two approaches I considered when creating the minimap:
/// 
/// 1. The use a Scene Capture/Render Target to display a birdeye view of the map,
/// each object to be shown on the minimap would possess an icon above their head
/// that could only be seen by the minimap.
/// 2. Create icons within the widget itself and calculating their positions within
/// the minimap widget based upon the actors location in relation to the map bounds.
///
/// I have decided upon the latter, deciding that it would more performant and allow
/// for reuse in other levels within additional actors, simply the bounds of the map.
///
/// Icons are handled through an object pool, initially I had tried to create a factory
/// that would create MinimapIcons, then display those on the MinimapWidget. However, I
/// had a lot of trouble getting them to spawn at the right size, in the right place and
/// anchored correctly. I overcame this by using an object pool, however the pool only supports
/// a limited number of icons (due to the instantiation problems)/

#pragma once

#include "CoreMinimal.h"
#include "EAllegiance.h"
#include "UIContent.h"
#include "Blueprint/UserWidget.h"
#include "MinimapWidget.generated.h"

UCLASS()
class LJMUBASIC425_API UMinimapWidget : public UUIContent
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Minimap")
	class UCanvasPanel* Panel;

	// Object pool
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Minimap")
	TArray<class UMinimapIcon*> MinimapIconPool;

	// Actors to display minimap icons for
	UPROPERTY()
	TArray<AActor*> ArrayOfActors;

	// Minimap colours
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Minimap")
	FColor FriendlyColour;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Minimap")
	FColor NeutralColour;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Minimap")
	FColor EnemyColour;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Minimap")
	UUserWidget* MinimapCameraIcon;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Minimap")
	class AStarfallCamera* Camera;
	
private:
	UPROPERTY()
	TMap<AActor*, UMinimapIcon*> MinimapIconMap;

	UPROPERTY(EditAnywhere, Category = "Minimap")
	float MinimapSize;

	UPROPERTY(EditAnywhere, Category = "Minimap")
	float LevelSize;

	UPROPERTY()
	TMap<EAllegiance, FColor> ColourMap;

	UPROPERTY()
	int32 PoolCount = 0;
	
	FTimerHandle TimerHandle;
	
public:
	virtual void NativeConstruct() override;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Minimap")
	void InitMinimap();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Minimap")
	void UpdateIconColour(UMinimapIcon* pIcon, FColor pColour);

private:
	UFUNCTION()
	void UpdateActors();

	UFUNCTION()
	static float FindAngle(FVector2D pFirstPoint, FVector2D pSecondPoint);

	UFUNCTION()
	static FVector2D FindCoords(float pRadius, float pDegrees);

	UFUNCTION()
	void UpdatePositions();

	UFUNCTION()
	void UpdateCameraIcon() const;

	UFUNCTION()
	void MinimapTick();

	UFUNCTION()
	UMinimapIcon* GetNextInPool(AActor* pActor);

	UFUNCTION()
	void AddBackToPool(AActor* pActor);
};
