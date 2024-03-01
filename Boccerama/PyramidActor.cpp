// Fill out your copyright notice in the Description page of Project Settings.

#include "PyramidActor.h"
#include "NiagaraComponent.h"
#include "NiagaraSystem.h"

// Sets default values
APyramidActor::APyramidActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	SM_Component = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	if (SM_Component)
	{
		RootComponent = SM_Component;
		SM_Asset = LoadObject<UStaticMesh>(nullptr, TEXT("/Script/Engine.StaticMesh'/Game/StarterContent/Shapes/Shape_QuadPyramid.Shape_QuadPyramid'"));

		if (SM_Asset)
		{
			SM_Component->SetStaticMesh(SM_Asset);
			SM_Component->SetWorldScale3D(FVector(4.0,4.0,4.0));
			
			// create a static loader for material -- do not load more than once (?)
			if (UMaterialInterface* Material = LoadObject<UMaterialInterface>(nullptr, TEXT("/Script/Engine.Material'/Game/StarterContent/Materials/M_Metal_Rust.M_Metal_Rust'")))
			{
				SM_Component->SetMaterial(0, Material);
			}
			else
			{
				UE_LOG(LogTemp, Error, TEXT("Failed to load material"))
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

	FSoftObjectPath AssetRef(TEXT("/Script/Niagara.NiagaraSystem'/Game/Levels/SpawnNiagraSystem.SpawnNiagraSystem'"));
	FxSpawn = Cast<UNiagaraSystem>(StaticLoadObject(UNiagaraSystem::StaticClass(), nullptr, *AssetRef.ToString()));
}

// Called when the game starts or when spawned
void APyramidActor::BeginPlay()
{
	Super::BeginPlay();
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
}

// Called every frame
void APyramidActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}



