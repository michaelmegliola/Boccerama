// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SimpleBallActor.generated.h"

UCLASS()
class BOCCERAMA_API ASimpleBallActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASimpleBallActor();
	
	UPROPERTY(EditAnywhere, Category="Mesh")
	class UStaticMesh* SM_Asset;

	UPROPERTY(EditAnywhere, Category="Mesh")
	class UStaticMeshComponent* SM_Component;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
