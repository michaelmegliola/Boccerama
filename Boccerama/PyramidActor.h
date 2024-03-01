// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "GameFramework/Actor.h"
#include "PyramidActor.generated.h"

UCLASS()
class BOCCERAMA_API APyramidActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APyramidActor();

	UPROPERTY(EditAnywhere, Category="Mesh")
	class UStaticMesh* SM_Asset;

	UPROPERTY(EditAnywhere, Category="Mesh")
	class UStaticMeshComponent* SM_Component;

	UPROPERTY(EditAnywhere, Category="FX")
	UNiagaraSystem* FxSpawn;

	UPROPERTY(EditAnywhere, Category="FX")
	UNiagaraComponent* FxComponent;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
