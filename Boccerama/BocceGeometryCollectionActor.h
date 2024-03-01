// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GeometryCollection/GeometryCollectionActor.h"
#include "BocceGeometryCollectionActor.generated.h"

/**
 * 
 */
UCLASS()
class BOCCERAMA_API ABocceGeometryCollectionActor : public AGeometryCollectionActor
{
	GENERATED_BODY()

public:
	ABocceGeometryCollectionActor();
	void SelfDestruct();
};
