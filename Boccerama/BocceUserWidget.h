// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "BocceUserWidget.generated.h"

UCLASS()
class BOCCERAMA_API UBocceUserWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;
	
	UPROPERTY(meta = (BindWidget))
	UButton* ButtonUp;

	UPROPERTY(meta = (BindWidget))
	UButton* ButtonDown;

	UPROPERTY(meta = (BindWidget))
	UButton* ButtonLeft;

	UPROPERTY(meta = (BindWidget))
	UButton* ButtonRight;

	UPROPERTY(meta = (BindWidget))
	UButton* ButtonFire;

	UPROPERTY(meta = (BindWidget))
	UButton* ButtonBall;

	UPROPERTY(meta = (BindWidget))
	UButton* ButtonBrick;

	UFUNCTION()
	void OnButtonUpClick();

	UFUNCTION()
	void OnButtonDownClick();

	UFUNCTION()
	void OnButtonLeftClick();

	UFUNCTION()
	void OnButtonRightClick();

	UFUNCTION()
	void OnButtonFireClick();

	UFUNCTION()
	void OnButtonBallClick();
	
	UFUNCTION()
	void OnButtonBrickClick();
};
