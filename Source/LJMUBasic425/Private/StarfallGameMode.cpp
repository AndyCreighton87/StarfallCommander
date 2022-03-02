// Fill out your copyright notice in the Description page of Project Settings.


#include "StarfallGameMode.h"

#include "GameManager.h"
#include "OrderManager.h"
#include "StarfallGameState.h"

void AStarfallGameMode::BeginPlay()
{
	Super::BeginPlay();

	// Spawn Actors
	OrderManager = GetWorld()->SpawnActor<AOrderManager>();
	GameManager = GetWorld()->SpawnActor<AGameManager>(GameManagerClass);
}

void AStarfallGameMode::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

void AStarfallGameMode::InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage)
{
	Super::InitGame(MapName, Options, ErrorMessage);
}

FString AStarfallGameMode::InitNewPlayer(APlayerController* NewPlayerController, const FUniqueNetIdRepl& UniqueNetId,
	const FString& Options, const FString& Portal)
{
	return Super::InitNewPlayer(NewPlayerController, UniqueNetId, Options, Portal);
}

void AStarfallGameMode::PreInitializeComponents()
{
	Super::PreInitializeComponents();
}

void AStarfallGameMode::SetPlayerDefaults(APawn* PlayerPawn)
{
	Super::SetPlayerDefaults(PlayerPawn);
}

void AStarfallGameMode::InitGameState()
{
	Super::InitGameState();
}

AOrderManager* AStarfallGameMode::GetOrderManager()
{
	return OrderManager;
}

AGameManager* AStarfallGameMode::GetGameManager()
{
	return GameManager;
}
