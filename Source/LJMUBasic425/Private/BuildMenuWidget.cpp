// Fill out your copyright notice in the Description page of Project Settings.


#include "BuildMenuWidget.h"

#include "BuildQueue.h"
#include "StarfallPlayerController.h"
#include "UIMainWidget.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"

void UBuildMenuWidget::SetButtons(TArray<FBuildableData> pBuildables, UObject* pBuilder)
{
	// Iterate through each Buildable and display the information on a button within the menu.
	// A delegate is added to StartBuild.
	for (const auto entry : pBuildables)
	{
		BuildButtons[Index]->SetVisibility(ESlateVisibility::Visible);
		BuildButtons[Index]->UpdateButtonData(entry.DisplayName, entry.DisplayImage);
		BuildButtons[Index]->SetBuildable(entry);
		BuildButtons[Index]->BindButton();
		BuildButtons[Index]->BuildButtonDelegate.AddDynamic(this, &UBuildMenuWidget::StartBuild);
		BuildButtons[Index]->Button->SetToolTipText(FText::FromString(FString::Printf(TEXT("Minerals: %d \nPopulation: %d"), entry.MineralCost, entry.PopulationCost)));
		BuildableMap.Add(entry.Type, entry);
		Index++;
	}

	Builder = Cast<IBuilder>(pBuilder);
}

void UBuildMenuWidget::ExitBuildMenu()
{
	// Upon exiting the Build Menu, Remove the Build Menu & Build Queue
	AStarfallPlayerController* tPlayerController = Cast<AStarfallPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	tPlayerController->GetUIWidget()->GetUIElement(EUIElements::RightPanel)->RemoveTopScreen();
	tPlayerController->GetUIWidget()->GetUIElement(EUIElements::MiddlePanel)->RemoveTopScreen();
	ClearUI();
}

void UBuildMenuWidget::ClearUI()
{
	for (const auto entry : BuildButtons)
	{
		entry->SetVisibility(ESlateVisibility::Hidden);
		entry->UpdateButtonData("", nullptr);
		entry->BuildButtonDelegate.RemoveAll(this);
		entry->RemoveBinding();
	}
	BuildableMap.Empty();
	Builder = nullptr;
	Index = 0;
}

// Called from delegate. Adds the associated buildable to the build queue.
// Can't be made const due to delegate.
void UBuildMenuWidget::StartBuild(FBuildableData pBuildable)
{
	if (Builder)
	{
		ABuildQueue* tBuildQueue = Builder->GetBuildQueue();
		tBuildQueue->AddToBuildQueue(pBuildable);
	}
}
