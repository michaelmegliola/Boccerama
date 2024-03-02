// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include <set>
#include "CoreMinimal.h"
#include "BaseBrickActor.h"
#include "NiagaraFunctionLibrary.h"
#include "GameFramework/Actor.h"
#include "BrickActor.generated.h"

UCLASS()
class BOCCERAMA_API ABrickActor : public ABaseBrickActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABrickActor();
	const int MAX_CHILD_COUNT = 24;
	void RequestDestroy();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	float SpawnTime;

private:
	std::set<ABaseBrickActor*> Children;
	FTimerHandle TimerHandle_Build;
	void BuildWall();
	int ChildCount;
	bool Stopped;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	void StartTicking();
};
