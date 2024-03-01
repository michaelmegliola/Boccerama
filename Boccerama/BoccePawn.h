// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "BoccePawn.generated.h"

UCLASS()
class BOCCERAMA_API ABoccePawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ABoccePawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Spotlight")
	class USpotLightComponent* SpotLight;

	UPROPERTY(EditAnywhere, Category = "UI")
	TSubclassOf<UUserWidget> MyUiClass;

	UPROPERTY(EditAnywhere, Category = "UI")
	UUserWidget* MyUiInstance;

	UPROPERTY(EditAnywhere, Category = "GamePlay")
	float MuzzleVelocity;

	void ElevateAim(float V);
	void RotateAim(float V);
	void Fire();
	void EquipBrick();
	void EquipBall();
	
private:
	void ToggleUiNow();
	float Elevation;
	float Direction;
	FTimerHandle TimerHandle_Flicker;
	FTimerHandle TimerHandle_Ui;
	void Flicker();
	bool Test;
	bool ToggleUi;
	int Weapon;
};
