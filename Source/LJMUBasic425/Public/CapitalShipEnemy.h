/// The CapitalShipEnemy class serves as the main enemy AI class within the game.
/// I'm unsure if this was the best way to do this, and I think that maybe having a
/// custom component that I could attach to a capital ship would have worked, however
/// I do like the easy access to the build queue to create units.
///
/// The class has two main roles.
/// 1. Spawn enemy Ships
/// 2. Launch waves of attacks on players capital ship
///
/// Alluded to within the BuildQueue class, I was unable to have the enemy have a resource
/// manager. Instead, I use the CreateBuildable function from the BuildQueue class to sidestep
/// the limitations. So in a sense the enemy AI "cheats", it builds ship that don't cost any
/// resources.
#pragma once

#include "CoreMinimal.h"
#include "CapitalShip.h"
#include "CapitalShipEnemy.generated.h"

UCLASS()
class LJMUBASIC425_API ACapitalShipEnemy : public ACapitalShip
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

private:
	// How often the capital ship will spawn a ship
	UPROPERTY(EditAnywhere, Category = "Ship | Enemy")
	float SpawnTimer = 2.0f;

	// How often the capital ship will order its army to attack player
	UPROPERTY(EditAnywhere, Category = "Ship | Enemy")
	float AttackTimer = 20.0f;

	// Timers
	FTimerHandle SpawnTimerHandle;

	FTimerDelegate SpawnTimerDelegate;

	FTimerHandle AttackTimerHandle;

	FTimerDelegate AttackTimerDelegate;

	// Keep track of ships created
	UPROPERTY()
	TArray<class ABaseShip*> Ships;

protected:
	// I needed to override this so I could clear timers on death.
	// Maybe there's a better way to do this, like a delegate that happens on Destroy actor?
	virtual void ManageDeath() override;

public:
	UFUNCTION()
	void ClearTimers();
	
	virtual void CleanUp() override;
	
private:
	UFUNCTION()
	void SpawnEnemyShip();

	UFUNCTION()
	void Attack();

	UFUNCTION()
	void RemoveFromShipList(ABaseShip* pBaseShip);
};
