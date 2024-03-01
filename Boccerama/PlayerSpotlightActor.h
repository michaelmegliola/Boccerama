// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SpotLightComponent.h"
#include "PlayerSpotlightActor.generated.h"

UCLASS()
class BOCCERAMA_API APlayerSpotlightActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APlayerSpotlightActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Spotlight")
	class USpotLightComponent* SpotLight;
	
private:
	FTimerHandle TimerHandle_Flicker;
	void Flicker();
};
