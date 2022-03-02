// Fill out your copyright notice in the Description page of Project Settings.


#include "BuildQueueWidget.h"

void UBuildQueueWidget::DisplayWarning()
{
	ShowWarningMessage();
	
	FTimerDelegate tTimerDelegate;
	tTimerDelegate.BindLambda([this]
	{
		if (this)
			HideWarningMessage();
	});

	GetWorld()->GetTimerManager().SetTimer(WarningMessageTimer, tTimerDelegate, TimeToDisplayWarning, false);
}

void UBuildQueueWidget::Update(TArray<FBuildableData> pBuildables)
{
	// Update the buttons with Buildable Data
	for (int i = 0; i < pBuildables.Num(); i++)
		BuildQueueIcons[i]->UpdateButtonData(pBuildables[i].DisplayName, pBuildables[i].DisplayImage);

	// Set the default image for any remaining buttons
	for (int i = pBuildables.Num(); i < BuildQueueIcons.Num(); i++)
		BuildQueueIcons[i]->UpdateButtonData("", BuildImage);
}

void UBuildQueueWidget::ClearUI()
{
	GetWorld()->GetTimerManager().ClearTimer(WarningMessageTimer);
}
