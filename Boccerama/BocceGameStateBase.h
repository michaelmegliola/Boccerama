// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BocceUserWidget.h"
#include "BoccePawn.h"
#include "GameFramework/GameStateBase.h"
#include "BocceGameStateBase.generated.h"

/**
 * 
 */
UCLASS()
class BOCCERAMA_API ABocceGameStateBase : public AGameStateBase
{
	GENERATED_BODY()
	
public:
	virtual void BeginPlay() override;
	void SetUiPanel(UBocceUserWidget* UiPanel);
	void HandleButtonEvent(int N);
	void RegisterPlayer(ABoccePawn* BP);

private:
	UBocceUserWidget* ControlPanel;
	ABoccePawn* Player;
};
