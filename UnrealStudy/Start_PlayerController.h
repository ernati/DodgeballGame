// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MainMenuWidget.h"
#include "Start_PlayerController.generated.h"

/**
 * 
 */
UCLASS()
class UNREALSTUDY_API AStart_PlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly)
		TSubclassOf<class UMainMenuWidget> BP_MainMenuWidget;

private:
	UPROPERTY()
		class UMainMenuWidget* MainMenuWidget;

protected:
	virtual void BeginPlay() override;
	
};
