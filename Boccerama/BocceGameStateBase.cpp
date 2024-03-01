// Fill out your copyright notice in the Description page of Project Settings.

#include "BocceGameStateBase.h"

#include "BoccePawn.h"
#include "PyramidActor.h"
#include "SimpleBallActor.h"
#include "Blueprint/UserWidget.h"
#include "Math/UnrealMathUtility.h"

void ABocceGameStateBase::BeginPlay()
{
	UWorld* const World = GetWorld();
	if (World)
	{
		for (int i = -1; i < 2; i++)
		{
			for (int j = -1; j < 2; j++)
			{
				FActorSpawnParameters SpawnParams;
				SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

				// Define the location and rotation for the spawned actor
				const float x = (i * 1600.f) + FMath::RandRange(-200.f,200.f);
				const float y = (j * 1600.f) + FMath::RandRange(-200.f,200.f);
				FVector SpawnLocation(x, y, FMath::RandRange(500.f, 1000.f));
				FRotator SpawnRotation(FMath::RandRange(-10.f,10.f), FMath::RandRange(-45.f,45.f), FMath::RandRange(-10.f,10.f));

				// Spawn the actor
				APyramidActor* SpawnedActor = World->SpawnActor<APyramidActor>(APyramidActor::StaticClass(), SpawnLocation, SpawnRotation, SpawnParams);
				if (SpawnedActor)
				{
					// Optional: Do something with the spawned actor
				}
			}
		}
	}

}

void ABocceGameStateBase::SetUiPanel(UBocceUserWidget* UiPanel)
{
	ControlPanel = UiPanel;
}

void ABocceGameStateBase::RegisterPlayer(ABoccePawn* BP)
{
	Player = BP;
}

void ABocceGameStateBase::HandleButtonEvent(int N)
{
	switch (N)
	{
	case 0:
		Player->ElevateAim(10.f);
		break;
	case 1:
		Player->ElevateAim(-10.f);
		break;
	case 2:
		Player->RotateAim(-5.f);
		break;
	case 3:
		Player->RotateAim(5.f);
		break;
	case 4:
		Player->Fire();
		break;
	case 5:
		Player->EquipBrick();
		break;
	case 6:
		Player->EquipBall();
		break;
	}
}

