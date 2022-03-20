// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "FPSGameMode.h"
#include "FPSHUD.h"
#include "FPSCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "UObject/ConstructorHelpers.h"

AFPSGameMode::AFPSGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/Blueprints/BP_Player"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = AFPSHUD::StaticClass();
}

void AFPSGameMode::CompleteMission(APawn* InstigatorPawn)
{
	if (InstigatorPawn)
	{
		InstigatorPawn->DisableInput(nullptr);
	}

	if (SpectatingViewpointClass)
	{
		AActor* NewViewTarget = nullptr;
		TArray<AActor*> ReturnedActors;
		UGameplayStatics::GetAllActorsOfClass(this, SpectatingViewpointClass, ReturnedActors);

		if (ReturnedActors.Num() > 0)
		{
			NewViewTarget = ReturnedActors[0];
		}
	
		APlayerController* PC = Cast<APlayerController>(InstigatorPawn->GetController());
		if (PC && NewViewTarget != nullptr)
		{
			PC->SetViewTargetWithBlend(NewViewTarget, .5f, EViewTargetBlendFunction::VTBlend_Cubic);
		}
	}
	else
	{
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(0, 10.f, FColor::White, "No SpectatingClass");
		}
	}

	OnMissionCompleted(InstigatorPawn);
}
