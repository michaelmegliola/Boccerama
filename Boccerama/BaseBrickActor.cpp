#include "BaseBrickActor.h"
#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraSystem.h"

ABaseBrickActor::ABaseBrickActor()
{
	PrimaryActorTick.bCanEverTick = false;
	
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
	}
	FSoftObjectPath AssetRef(TEXT("/Script/Niagara.NiagaraSystem'/Game/Levels/SpawnNiagraSystem.SpawnNiagraSystem'"));
	FxSpawn = Cast<UNiagaraSystem>(StaticLoadObject(UNiagaraSystem::StaticClass(), nullptr, *AssetRef.ToString()));
}

void ABaseBrickActor::RequestDestroy()
{
	UNiagaraComponent* NiagaraComp = UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, FxSpawn, GetActorLocation(), FRotator::ZeroRotator);
	if (NiagaraComp)
	{
		NiagaraComp->Activate();
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Could not acquire pointer to Niagra component"));
	}
	Destroy();
}


