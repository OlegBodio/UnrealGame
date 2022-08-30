// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "NewGameMode.generated.h"

/**
 * 
 */
UCLASS()
class GAME_API ANewGameMode : public AGameMode
{
	GENERATED_BODY()

public:
	UFUNCTION()
		void MyResetLevel();
	
};
