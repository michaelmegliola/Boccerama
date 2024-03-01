// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "BocceGameMode.generated.h"

/**
 * 
 */
UCLASS()
class BOCCERAMA_API ABocceGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	ABocceGameMode();
	virtual void BeginPlay() override;
};
