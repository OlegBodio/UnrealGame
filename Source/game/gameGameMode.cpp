// Copyright Epic Games, Inc. All Rights Reserved.

#include "gameGameMode.h"
#include "gameHUD.h"
#include "gameCharacter.h"
#include "UObject/ConstructorHelpers.h"

AgameGameMode::AgameGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPersonCPP/Blueprints/FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = AgameHUD::StaticClass();
}
