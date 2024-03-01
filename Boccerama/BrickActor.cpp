// Fill out your copyright notice in the Description page of Project Settings.

#include "BrickActor.h"
#include "BaseBrickActor.h"

ABrickActor::ABrickActor()
{
	PrimaryActorTick.bCanEverTick = true;
	ChildCount = 0;
}

void ABrickActor::StartTicking()
{
	SetActorTickEnabled(true);
	GetWorldTimerManager().SetTimer(TimerHandle_Build, this, &ABrickActor::BuildWall, 0.5, true, 1.0);
}

// Called when the game starts or when spawned
void ABrickActor::BeginPlay()
{
	Super::BeginPlay();
	SpawnTime = GetWorld()->GetTime().GetWorldTimeSeconds();
}

void ABrickActor::BuildWall()
{
	if (ChildCount < MAX_CHILD_COUNT && GetVelocity() == FVector::ZeroVector)
	{
		FActorSpawnParameters SpawnParams;
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		FVector Loc = GetActorLocation();
		FVector Fwd = GetActorForwardVector();
		ChildCount += 1;
		FVector Here = Loc+(Fwd*210)*(ChildCount % 5);
		Here.Z += (ChildCount / 5) * 110;
		ABaseBrickActor* BBA = GetWorld()->SpawnActor<ABaseBrickActor>(ABaseBrickActor::StaticClass(), Here, GetActorRotation(), SpawnParams);
		Children.insert(BBA);
	}
}

// Called every frame
void ABrickActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (GetWorld()->GetTime().GetWorldTimeSeconds() - SpawnTime > 30.0)
	{
		RequestDestroy();
	}
}

void ABrickActor::RequestDestroy()
{
	for (ABaseBrickActor* Child : Children)
	{
		Child->RequestDestroy();
	}
	ABaseBrickActor::RequestDestroy();
}




