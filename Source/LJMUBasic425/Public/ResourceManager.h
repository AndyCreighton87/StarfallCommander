/// Class that keeps tracks of players resources including Minerals and Population.
/// Makes use of a custom tick to provide the player with a steady rate of minerals.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameFramework/Info.h"
#include "ResourceManager.generated.h"

// Delegate that passes resource information. Used by ResourceWidget.
DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FResourcesUpdated, int32, Minerals, int32, MineralValue, int32, Population, int32, PopulationLimit);

UCLASS()
class LJMUBASIC425_API AResourceManager : public AInfo
{
	GENERATED_BODY()
	
public:	
	AResourceManager();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

public:
	// Starting values
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Resources")
	int32 StartingMinerals;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Resources")
	int32 PopulationLimit;

	// Delegates
	FResourcesUpdated ResourcesUpdatedDelegate;

private:
	// Resources
	UPROPERTY(VisibleAnywhere, Category = "Resources")
	int32 Minerals;

	UPROPERTY(VisibleAnywhere, Category = "Resources")
	int32 MineralTickValue = 1.0f;

	UPROPERTY(VisibleAnywhere, Category = "Resources")
	int32 CurrentPopulation;

	// Timers
	FTimerHandle TimerHandle;

public:
	UFUNCTION()
	void Init();
	
	UFUNCTION(BlueprintCallable, Category = "Resources")
	void DeductMinerals(int32 pAmount);

	UFUNCTION(BlueprintCallable, Category = "Resources")
	void AddMinerals(int32 pAmount);

	UFUNCTION(BlueprintCallable, Category = "Resources")
	bool CheckPopulationLimit(int32 pPopCost);

	UFUNCTION(BlueprintCallable, Category = "Resources")
	bool CheckSufficientMinerals(int32 pCost);

	UFUNCTION(BlueprintCallable, Category = "Resources")
	void IncreaseMineralTick();

	UFUNCTION(BlueprintCallable, Category = "Resources")
	void DecreaseMineralTick();

	UFUNCTION(BlueprintCallable, Category = "Resources")
	void IncreasePopulation(int32 pAmount);

	UFUNCTION(BlueprintCallable, Category = "Resources")
	void DecreasePopulation(int32 pAmount);

private:
	UFUNCTION()
	void MineralTick();
};
