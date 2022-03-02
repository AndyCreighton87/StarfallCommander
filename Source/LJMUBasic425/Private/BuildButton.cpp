// Fill out your copyright notice in the Description page of Project Settings.


#include "BuildButton.h"

#include "Components/Button.h"

FBuildableData UBuildButton::GetBuildable() const
{
	return Buildable;
}

void UBuildButton::SetBuildable(FBuildableData pBuildable)
{
	Buildable = pBuildable;
}

void UBuildButton::BindButton()
{
	Button->OnClicked.AddDynamic(this, &UBuildButton::OnBuildButtonPressed);
}

void UBuildButton::RemoveBinding() const
{
	Button->OnClicked.RemoveAll(this);
}

// Can't be const as I'm using it within a delegate
void UBuildButton::OnBuildButtonPressed()
{
	BuildButtonDelegate.Broadcast(Buildable);
}

