// Fill out your copyright notice in the Description page of Project Settings.


#include "CapitalShipEnemy.h"

#include "BuildQueue.h"
#include "EShipAIState.h"
#include "StarfallGameMode.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"

void ACapitalShipEnemy::BeginPlay()
{
	Super::BeginPlay();

	// Set up Spawn Timer
	SpawnTimerDelegate.BindLambda([this]
	{
		if (this || !IsPendingKill())
			SpawnEnemyShip();
	});

	GetWorld()->GetTimerManager().SetTimer(SpawnTimerHandle, SpawnTimerDelegate, SpawnTimer, false);

	// Set up Attack Timer
	AttackTimerDelegate.BindLambda([this]
	{
		if (this || !IsPendingKill())
			Attack();
	});

	GetWorld()->GetTimerManager().SetTimer(AttackTimerHandle, AttackTimerDelegate, AttackTimer, false);
}

// Spawn a new enemy ship at random. Because the ship spawned is random, this could lead to unfair
// gameplay situations. While unlikely, it's possible for the enemy ship to produce 10+ Corvettes
// in a row, making it hard for the player to win. While variance is not inherently bad, I have
// counteracted the potential of this by increasing the frequency of attacks. Attacks more often with
// fewer ships should stop these deathball scenarios from occuring.
void ACapitalShipEnemy::SpawnEnemyShip()
{
	if (BuildQueue)
	{
		const int32 tIndex = FMath::RandRange(0, Buildables.Num() - 1);
		const auto tBuildable = BuildQueue->CreateBuildable(Buildables[tIndex]);
		const auto tShip = Cast<ABaseShip>(tBuildable.GetObject());
		tShip->ShipDeathDelegate.AddDynamic(this, &ACapitalShipEnemy::RemoveFromShipList);
		Ships.Add(tShip);
	}
	
	GetWorld()->GetTimerManager().SetTimer(SpawnTimerHandle, SpawnTimerDelegate, SpawnTimer, false);
}

// The capital ship orders all ships that have been created since the last attack to move to and then
// destroy the enemy capital ship. A ship will only be ordered to do so if it is not currently engaged
// in combat. I have used the Attack Order and behaviour tree to program this behaviour.
// When an attack is issued the Ships array is emptied.
void ACapitalShipEnemy::Attack()
{
	AStarfallGameMode* tGameMode = Cast<AStarfallGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
	ABaseShip* tTarget = tGameMode->GetGameManager()->GetCapitalShip(EAllegiance::Friendly);
	
	for (const auto entry : Ships)
	{
		if (!entry)
			continue;
		
		if (entry->Blackboard->GetValueAsEnum("State") != static_cast<uint8>(EShipAIState::Attack))
		{
			Cast<ACombatShip>(entry)->SetTargetShip(tTarget);
			entry->Blackboard->SetValueAsObject("TargetShip", tTarget);
			entry->Blackboard->SetValueAsEnum("State", static_cast<uint8>(EShipAIState::Attack));
		}
	}
	GetWorld()->GetTimerManager().SetTimer(AttackTimerHandle, AttackTimerDelegate, AttackTimer, false);

	Ships.Empty();
}

// Remove the ship from the Ship array upon its death.
// Will happen if a ship has been destroyed before an attack order is issued.
void ACapitalShipEnemy::RemoveFromShipList(ABaseShip* pBaseShip)
{
	if (Ships.Contains(pBaseShip))
	{
		pBaseShip->ShipDeathDelegate.RemoveAll(this);
		Ships.Remove(pBaseShip);
	}
}

void ACapitalShipEnemy::ManageDeath()
{
	ClearTimers();
	Super::ManageDeath();
}

void ACapitalShipEnemy::ClearTimers()
{
	GetWorld()->GetTimerManager().ClearTimer(SpawnTimerHandle);
	GetWorld()->GetTimerManager().ClearTimer(AttackTimerHandle);
}

void ACapitalShipEnemy::CleanUp()
{
	Super::CleanUp();
	ClearTimers();
}
