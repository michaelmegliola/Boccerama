// Fill out your copyright notice in the Description page of Project Settings.


#include "SimpleBallActor.h"

// Sets default values
ASimpleBallActor::ASimpleBallActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	SM_Component = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	if (SM_Component)
	{
		RootComponent = SM_Component;
		SM_Asset = LoadObject<UStaticMesh>(nullptr, TEXT("/Script/Engine.StaticMesh'/Game/StarterContent/Shapes/Shape_Sphere.Shape_Sphere'"));

		if (SM_Asset)
		{
			SM_Component->SetStaticMesh(SM_Asset);
			SM_Component->SetWorldScale3D(FVector(3.0,3.0,3.0));
			
			// create a static loader for material -- do not load more than once (?)
			if (UMaterialInterface* Material = LoadObject<UMaterialInterface>(nullptr, TEXT("/Script/Engine.Material'/Game/StarterContent/Materials/RedBall.RedBall'")))
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
}

// Called when the game starts or when spawned
void ASimpleBallActor::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ASimpleBallActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (GetActorLocation().Z < -200.0)
	{
		Destroy();
	}
}

