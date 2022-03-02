#include "Ability.h"

#include "EngineUtils.h"
#include "StarfallGameMode.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"

AAbility::AAbility()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AAbility::BeginPlay()
{
	Super::BeginPlay();
	OrderManager = Cast<AStarfallGameMode>(UGameplayStatics::GetGameMode(GetWorld()))->GetOrderManager();
}

void AAbility::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AAbility::Init(ABaseShip* pBaseShip)
{
	OwningShip = pBaseShip;
}

bool AAbility::GetIsOnCooldown()
{
	return IsOnCooldown;
}

ABaseShip* AAbility::GetOwningShip()
{
	return OwningShip;
}

void AAbility::OnActivate()
{
	GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Blue, FString::Printf(TEXT("Ability Activated: %s"), *ActivitableData.DisplayName));
}

FActivitableData AAbility::GetActivitableData()
{
	return ActivitableData;
}

FString AAbility::GetName()
{
	return ActivitableData.DisplayName;
}

void AAbility::BindToButton(UButton* pButton)
{
	UIButton = pButton;
	pButton->OnClicked.AddUniqueDynamic(this, &AAbility::OnActivate);
}

void AAbility::RemoveBinding()
{
	if(UIButton)
	{
		UIButton->OnClicked.RemoveAll(this);
		UIButton = nullptr;
	}
}

