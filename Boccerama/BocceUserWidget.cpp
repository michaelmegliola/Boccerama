// Fill out your copyright notice in the Description page of Project Settings.


#include "BocceUserWidget.h"

#include "BocceGameStateBase.h"


void UBocceUserWidget::NativeConstruct()
{
	Super::NativeConstruct();

	ButtonUp->OnClicked.AddDynamic(this, &UBocceUserWidget::OnButtonUpClick);
	ButtonDown->OnClicked.AddDynamic(this, &UBocceUserWidget::OnButtonDownClick);
	ButtonLeft->OnClicked.AddDynamic(this, &UBocceUserWidget::OnButtonLeftClick);
	ButtonRight->OnClicked.AddDynamic(this, &UBocceUserWidget::OnButtonRightClick);
	ButtonFire->OnClicked.AddDynamic(this, &UBocceUserWidget::OnButtonFireClick);
	ButtonBall->OnClicked.AddDynamic(this, &UBocceUserWidget::OnButtonBallClick);
	ButtonBrick->OnClicked.AddDynamic(this, &UBocceUserWidget::OnButtonBrickClick);

	GetWorld()->GetGameState<ABocceGameStateBase>()->SetUiPanel(this);
}

void UBocceUserWidget::OnButtonUpClick()
{
	GetWorld()->GetGameState<ABocceGameStateBase>()->HandleButtonEvent(0);
}

void UBocceUserWidget::OnButtonDownClick()
{
	GetWorld()->GetGameState<ABocceGameStateBase>()->HandleButtonEvent(1);
}

void UBocceUserWidget::OnButtonLeftClick()
{
	GetWorld()->GetGameState<ABocceGameStateBase>()->HandleButtonEvent(2);
}

void UBocceUserWidget::OnButtonRightClick()
{
	GetWorld()->GetGameState<ABocceGameStateBase>()->HandleButtonEvent(3);
}

void UBocceUserWidget::OnButtonFireClick()
{
	GetWorld()->GetGameState<ABocceGameStateBase>()->HandleButtonEvent(4);
}

void UBocceUserWidget::OnButtonBrickClick()
{
	GetWorld()->GetGameState<ABocceGameStateBase>()->HandleButtonEvent(5);
}

void UBocceUserWidget::OnButtonBallClick()
{
	GetWorld()->GetGameState<ABocceGameStateBase>()->HandleButtonEvent(6);
}

