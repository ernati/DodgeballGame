// Fill out your copyright notice in the Description page of Project Settings.


#include "Start_PlayerController.h"

void AStart_PlayerController::BeginPlay()
{
	Super::BeginPlay();

	/*SetPause(true);*/

	SetInputMode(FInputModeUIOnly());
	bShowMouseCursor = true;

	if (BP_MainMenuWidget != nullptr)
	{
		MainMenuWidget = CreateWidget<UMainMenuWidget>(this, BP_MainMenuWidget);
		MainMenuWidget->AddToViewport();
	}
}

