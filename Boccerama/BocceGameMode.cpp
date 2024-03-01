// Fill out your copyright notice in the Description page of Project Settings.


#include "BocceGameMode.h"
#include "BocceGameStateBase.h"
#include "BoccePlayerController.h"

ABocceGameMode::ABocceGameMode()
{
	GameStateClass = ABocceGameStateBase::StaticClass();
}

void ABocceGameMode::BeginPlay()
{

}
