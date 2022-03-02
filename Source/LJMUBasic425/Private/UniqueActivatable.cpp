#include "UniqueActivatable.h"

#include "StarfallPlayerController.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"

AUniqueActivatable::AUniqueActivatable()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AUniqueActivatable::BeginPlay()
{
	Super::BeginPlay();
}

void AUniqueActivatable::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

ABaseShip* AUniqueActivatable::GetOwningShip()
{
	return OwningShip;
}

void AUniqueActivatable::Init(ABaseShip* pBaseShip)
{
	OwningShip = pBaseShip;
}

void AUniqueActivatable::OnActivate()
{
	Execute();
}

FActivitableData AUniqueActivatable::GetActivitableData()
{
	return ActivitableData;
}

FString AUniqueActivatable::GetName()
{
	return ActivitableData.DisplayName;
}

void AUniqueActivatable::BindToButton(UButton* pButton)
{
	UIButton = pButton;
	pButton->OnClicked.AddUniqueDynamic(this, &AUniqueActivatable::OnActivate);
}

void AUniqueActivatable::RemoveBinding()
{
	if(UIButton)
	{
		UIButton->OnClicked.RemoveAll(this);
		UIButton = nullptr;
	}
}

