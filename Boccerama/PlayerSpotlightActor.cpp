// Fill out your copyright notice in the Description page of Project Settings.
#include "PlayerSpotlightActor.h"
#include "GameFramework/Actor.h"
#include "Components/PointLightComponent.h"

// Sets default values
APlayerSpotlightActor::APlayerSpotlightActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Create and configure the light component
	SpotLight = CreateDefaultSubobject<USpotLightComponent>(TEXT("SpotLight"));
	RootComponent = SpotLight; // Or attach to another component as needed
	SpotLight->SetLightColor(FLinearColor::Green);
	SpotLight->SetIntensity(750000.0f);
	SpotLight->SetAttenuationRadius(1000.0f);
	SpotLight->SetOuterConeAngle(20.0f);
	SpotLight->SetCastShadows(false); // Optional
	SpotLight->SetLightFunctionFadeDistance(700.0);
}

// Called when the game starts or when spawned
void APlayerSpotlightActor::BeginPlay()
{
	Super::BeginPlay();
	SetActorLocation(FVector(-5000.0,0.0,600.0));
	GetWorldTimerManager().SetTimer(TimerHandle_Flicker, this, &APlayerSpotlightActor::Flicker, 0.25, true, 3.0);
}

void APlayerSpotlightActor::Flicker()
{
	SpotLight->SetVisibility(!SpotLight->GetVisibleFlag());
}

// Called every frame
void APlayerSpotlightActor::Tick(float DeltaTime)
{
	if (GetWorld()->GetTimeSeconds() > 3.75)
	{
		FVector loc = GetActorLocation();
		SetActorLocation(FVector(loc.X+500.0*DeltaTime, loc.Y, loc.Z));
	}
	/*
	FRotator rot = GetActorRotation();
	FMath::ClampAngle(rot.Pitch, 0.0f, 360.0f);
	SetActorRotation(rot);
	*/

}



