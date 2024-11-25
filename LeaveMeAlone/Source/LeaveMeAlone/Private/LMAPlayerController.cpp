// Fill out your copyright notice in the Description page of Project Settings.


#include "D:\Games2024\Task\Ta_3\LeaveMeAlone\Source\LeaveMeAlone\Public\LMAPlayerController.h"

ALMAPlayerController::ALMAPlayerController()
{
}

void ALMAPlayerController::BeginPlay()
{
	Super::BeginPlay();

	SetInputMode(FInputModeGameOnly());
	bShowMouseCursor = false;
}