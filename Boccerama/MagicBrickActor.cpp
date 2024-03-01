// Fill out your copyright notice in the Description page of Project Settings.


#include "MagicBrickActor.h"
#include "NiagaraComponent.h"
#include "NiagaraSystem.h"

// Sets default values
AMagicBrickActor::AMagicBrickActor()
{
	SM_Component = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	if (SM_Component)
	{
		RootComponent = SM_Component;
		SM_Asset = LoadObject<UStaticMesh>(nullptr, TEXT("/Script/Engine.StaticMesh'/Game/StarterContent/Shapes/Shape_Cube.Shape_Cube'"));

		if (SM_Asset)
		{
			SM_Component->SetStaticMesh(SM_Asset);
			SM_Component->SetWorldScale3D(FVector(2.0,1.0,1.0));

			// create a static loader for material -- do not load more than once (?)
			if (UMaterialInterface* Material = LoadObject<UMaterialInterface>(nullptr, TEXT("/Script/Engine.Material'/Game/StarterContent/Materials/M_Brick_Clay_New.M_Brick_Clay_New'")))
			{
				SM_Component->SetMaterial(0, Material);
				SM_Component->SetMassOverrideInKg(NAME_None, 1000.0);
			}
			else
			{
				UE_LOG(LogTemp, Error, TEXT("Failed to load material"));
			}

			// Enable physics simulation
			SM_Component->SetSimulatePhysics(true);

			// Optionally, set collision properties
			SM_Component->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
			SM_Component->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);
			SM_Component->SetCollisionObjectType(ECollisionChannel::ECC_PhysicsBody);

		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("Failed to create static mesh asset"));
		}
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to create static mesh component"));
	}
	/*
	FSoftObjectPath AssetRef(TEXT("/Script/Niagara.NiagaraSystem'/Game/Levels/SpawnNiagraSystem.SpawnNiagraSystem'"));
	FxSpawn = Cast<UNiagaraSystem>(StaticLoadObject(UNiagaraSystem::StaticClass(), nullptr, *AssetRef.ToString()));
	*/
	UE_LOG(LogTemp, Warning, TEXT("brick 0"));
}

// Called when the game starts or when spawned
void AMagicBrickActor::BeginPlay()
{
	Super::BeginPlay();
	SetActorTickEnabled(true);
	UE_LOG(LogTemp, Warning, TEXT("brick 1"));
	//SpawnTime = GetWorld()->GetTime().GetWorldTimeSeconds();
}


// Called every frame
void AMagicBrickActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	UE_LOG(LogTemp, Warning, TEXT("brick tick"));
	/*
	UE_LOG(LogTemp, Warning, TEXT("time %.2f %.2f"), SpawnTime, GetWorld()->GetTime().GetWorldTimeSeconds());
	if (GetWorld()->GetTime().GetWorldTimeSeconds() - SpawnTime > 5.0)
	{
		if (FxSpawn)
		{
			UNiagaraComponent* NiagaraComp = UNiagaraFunctionLibrary::SpawnSystemAttached(FxSpawn, SM_Component, NAME_None, FVector(0.f), FRotator(0.f), EAttachLocation::Type::KeepRelativeOffset, true);
			if (NiagaraComp)
			{
				NiagaraComp->Activate();
			}
			else
			{
				UE_LOG(LogTemp, Error, TEXT("Could not acquire pointer to Niagra component"));
			}
		}
		Destroy();
	}
	*/
}

