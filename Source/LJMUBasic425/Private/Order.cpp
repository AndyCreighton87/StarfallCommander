// Fill out your copyright notice in the Description page of Project Settings.


#include "Order.h"

#include "AIController.h"
#include "BaseShip.h"
#include "EngineUtils.h"
#include "OrderManager.h"
#include "StarfallGameMode.h"
#include "UIButton.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"

AOrder::AOrder()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AOrder::BeginPlay()
{
	Super::BeginPlay();
	
	// Get Order Manager
	OrderManager = Cast<AStarfallGameMode>(UGameplayStatics::GetGameMode(GetWorld()))->GetOrderManager();
}

void AOrder::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AOrder::Init(ABaseShip* pBaseShip)
{
	OwningShip = pBaseShip;
}

void AOrder::OnActivate()
{
	if (!OrderManager->GetIsCurrentlyIssuingOrder())
		SetAIState();
}

FActivitableData AOrder::GetActivitableData()
{
	return ActivitableData;
}

FString AOrder::GetName()
{
	return ActivitableData.DisplayName;
}

void AOrder::BindToButton(UButton* pButton)
{
	// If additional input is required, Add it to pending orders in the order manager.
	UIButton = pButton;
	if (bRequiresInput)
		pButton->OnClicked.AddDynamic(this, &AOrder::AddToPending);
	else
		pButton->OnClicked.AddDynamic(this, &AOrder::OnActivate);
}

void AOrder::RemoveBinding()
{
	// Clears any binding to OnClicked
	if(UIButton)
	{
		UIButton->OnClicked.RemoveAll(this);
		UIButton = nullptr;
	}
}

void AOrder::AddToPending()
{
	OrderManager->AddOrderToPending(this);
}

