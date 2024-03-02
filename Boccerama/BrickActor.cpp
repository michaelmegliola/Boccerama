// Fill out your copyright notice in the Description page of Project Settings.

#include "BrickActor.h"
#include "BaseBrickActor.h"
#include "PhysicsEngine/RadialForceActor.h"

ABrickActor::ABrickActor()
{
	PrimaryActorTick.bCanEverTick = true;
	ChildCount = 0;
	Stopped = false;
}

void ABrickActor::StartTicking()
{
	SetActorTickEnabled(true);
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
	
	if (!Stopped && (GetVelocity() == FVector::ZeroVector) && GetWorld()->GetTime().GetWorldTimeSeconds()-SpawnTime > 1.0)
	{
		Stopped = true;
		const FRotator Orientation = GetActorRotation();
		int NYaw = static_cast<int>(Orientation.GetComponentForAxis(EAxis::Z));
		NYaw /= 45;
		NYaw *= 45;
		
		SetActorRotation(FRotator(0.0, NYaw, 0.0));
		GetWorldTimerManager().SetTimer(TimerHandle_Build, this, &ABrickActor::BuildWall, 0.3, true, 0.5);
	}
	if (GetWorld()->GetTime().GetWorldTimeSeconds() - SpawnTime > 30.0)
	{
		RequestDestroy();
	}
}

void ABrickActor::RequestDestroy()
{
	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	ARadialForceActor* RFA = GetWorld()->SpawnActor<ARadialForceActor>(ARadialForceActor::StaticClass(), GetActorLocation(), GetActorRotation(), SpawnParams);
	URadialForceComponent* RFC = Cast<URadialForceComponent>(RFA->GetComponentByClass(URadialForceComponent::StaticClass()));
	RFC->Radius = 24000.0;
	RFC->Falloff = RIF_Linear;
	RFC->ImpulseStrength = 1000000.0;
	RFC->AddCollisionChannelToAffect(ECC_PhysicsBody);
	RFC->AddCollisionChannelToAffect(ECC_WorldDynamic);
	RFC->FireImpulse();
	
	for (ABaseBrickActor* Child : Children)
	{
		Child->RequestDestroy();
	}
	ABaseBrickActor::RequestDestroy();
}




