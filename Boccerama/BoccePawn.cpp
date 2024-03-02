// Fill out your copyright notice in the Description page of Project Settings.

#include "BoccePawn.h"

#include "BocceGameStateBase.h"
#include "MagicBrickActor.h"
#include "SimpleBallActor.h"
#include "BrickActor.h"
#include "Blueprint/UserWidget.h"
#include "Components/SpotLightComponent.h"

// Sets default values
ABoccePawn::ABoccePawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Test = true;
	ToggleUi = true;
	Elevation = 0.f;
	Direction = 0.f;
	
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
void ABoccePawn::BeginPlay()
{
	Super::BeginPlay();

	Weapon = 0; // ball
	
	GetWorld()->GetGameState<ABocceGameStateBase>()->RegisterPlayer(this);
	SetActorLocation(FVector(-5000.0,0.0,400.0));
	GetWorldTimerManager().SetTimer(TimerHandle_Flicker, this, &ABoccePawn::Flicker, 0.25, true, 3.0);
	GetWorldTimerManager().SetTimer(TimerHandle_Ui, this, &ABoccePawn::ToggleUiNow, 3.0, true, 3.0);
	if (MyUiClass)
	{
		MyUiInstance = CreateWidget<UUserWidget>(GetWorld(), MyUiClass);
		if (MyUiInstance)
		{
			MyUiInstance->AddToViewport();
			MyUiInstance->SetVisibility(ESlateVisibility::Hidden);
		}
	}
	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
	if (PlayerController)
	{
		// Make the cursor visible
		PlayerController->bShowMouseCursor = true;

		// Enable the mouse to move freely
		PlayerController->SetInputMode(FInputModeUIOnly());
	}
}

void ABoccePawn::ToggleUiNow()
{
	if (ToggleUi)
	{
		MyUiInstance->SetVisibility(ESlateVisibility::Visible);
	}
	else
	{
		MyUiInstance->SetVisibility(ESlateVisibility::Hidden);
	}
	ToggleUi = !ToggleUi;
}

void ABoccePawn::ElevateAim(float V)
{
	Elevation += V;
	Elevation = FMath::Clamp(Elevation, -10.f, 45.f);
}

void ABoccePawn::RotateAim(float V)
{
	Direction += V;
	Direction = FMath::Clamp(Direction, -45.f, 45.f);
}

void ABoccePawn::Fire()
{
	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	if (Weapon == 0)
	{
		ASimpleBallActor* SBA = GetWorld()->SpawnActor<ASimpleBallActor>(ASimpleBallActor::StaticClass(), GetActorLocation(), FRotator(Elevation,Direction,0.0), SpawnParams);
		//ABrickActor* SBA = GetWorld()->SpawnActor<ABrickActor>(ABrickActor::StaticClass(), GetActorLocation(), FRotator(Elevation,Direction,0.0), SpawnParams);
		SBA->SM_Component->AddImpulse(SBA->GetActorForwardVector() * MuzzleVelocity, NAME_None, true);
	}
	else
	{
		float elev = FMath::Clamp(Elevation * 2.0, 10.0, 80.0);
		ABrickActor* MBA = GetWorld()->SpawnActor<ABrickActor>(ABrickActor::StaticClass(), GetActorLocation(), FRotator(elev,Direction,0.0), SpawnParams);
		MBA->SM_Component->AddImpulse(MBA->GetActorForwardVector() * MuzzleVelocity/3.0, NAME_None, true);
		MBA->SM_Component->AddTorqueInDegrees(FVector(FMath::RandRange(20000.0,80000.0),
													  FMath::RandRange(20000.0,80000.0),
													  FMath::RandRange(20000.0,80000.0)),
													  NAME_None, true);
		MBA->StartTicking();
	}
}

// Called every frame
void ABoccePawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void ABoccePawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void ABoccePawn::Flicker()
{
	SpotLight->SetVisibility(!SpotLight->GetVisibleFlag());
}

void ABoccePawn::EquipBall()
{
	Weapon = 0;
}

void ABoccePawn::EquipBrick()
{
	Weapon = 1;
}


