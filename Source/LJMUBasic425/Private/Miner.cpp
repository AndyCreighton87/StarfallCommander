// Fill out your copyright notice in the Description page of Project Settings.


#include "Miner.h"

#include "IMinable.h"
#include "ResourceManager.h"
#include "StarfallPlayerController.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"

void AMiner::BeginPlay()
{
	Super::BeginPlay();

	// Set up delegates for overlaps
	BoxCollider->SetGenerateOverlapEvents(true);
	BoxCollider->OnComponentBeginOverlap.AddDynamic(this, &AMiner::OnBeginOverlap);
	BoxCollider->OnComponentEndOverlap.AddDynamic(this, &AMiner::OnEndOverlap);
}

// Increase the mineral tick rate if OtherActor is IMinable.
void AMiner::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                            UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (Cast<IMinable>(OtherActor))
	{
		AStarfallPlayerController* tPlayerController = Cast<AStarfallPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
		tPlayerController->GetResourceManager()->IncreaseMineralTick();
	}
}

// Decrease the mineral tick rate if OtherActor is IMinable.
void AMiner::OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex)
{
	if (Cast<IMinable>(OtherActor))
	{
		AStarfallPlayerController* tPlayerController = Cast<AStarfallPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
		tPlayerController->GetResourceManager()->DecreaseMineralTick();
	}
}
