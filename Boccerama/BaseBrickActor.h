#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "NiagaraFunctionLibrary.h"
#include "PhysicsEngine/RadialForceComponent.h"
#include "BaseBrickActor.generated.h"

UCLASS()
class BOCCERAMA_API ABaseBrickActor : public AActor
{
	GENERATED_BODY()
	
public:
	ABaseBrickActor();
	void RequestDestroy();
	
	UPROPERTY(EditAnywhere, Category="Mesh")
	class UStaticMesh* SM_Asset;

	UPROPERTY(EditAnywhere, Category="Mesh")
	class UStaticMeshComponent* SM_Component;

	UPROPERTY(EditAnywhere, Category="FX")
	UNiagaraSystem* FxSpawn;

	UPROPERTY(EditAnywhere, Category="FX")
	UNiagaraComponent* FxComponent;

	//UPROPERTY(EditAnywhere, Category = "Components")
	//URadialForceComponent* RadialForceComponent;
};
