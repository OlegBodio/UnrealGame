// Fill out your copyright notice in the Description page of Project Settings.


#include "NewGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "SphereToSpawn.h"

void ANewGameMode::MyResetLevel()//Reset level
{
	UGameplayStatics::OpenLevel(GetWorld(), "Map2");//(FName)GetWorld()->GetMapName() потрібно створити папку з мапами в іншому місці і
	//тоді при проходженні різних левелів буде респавнитись саме потрібний девел
	ASphereToSpawn::SetSpeed(150.0f);
}