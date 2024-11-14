// Fill out your copyright notice in the Description page of Project Settings.

#include "LMAGameMode.h"
#include "LMADefaultCharacter.h"
#include "LMAPlayerController.h"



//#include "D:\Games2024\Task\Ta_3\LeaveMeAlone\Source\LeaveMeAlone\Public\LMAGameMode.h"
//#include "D:\Games2024\Task\Ta_3\LeaveMeAlone\Source\LeaveMeAlone\Public\LMADefaultCharacter.h"
//#include "D:\Games2024\Task\Ta_3\LeaveMeAlone\Source\LeaveMeAlone\Public\LMAPlayerController.h"

ALMAGameMode::ALMAGameMode()
{
	DefaultPawnClass = ALMADefaultCharacter::StaticClass();
	PlayerControllerClass = ALMAPlayerController::StaticClass();
}
