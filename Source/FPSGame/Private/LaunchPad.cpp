// Fill out your copyright notice in the Description page of Project Settings.


#include "LaunchPad.h"

#include "FPSCharacter.h"
#include "Components/BoxComponent.h"

// Sets default values
ALaunchPad::ALaunchPad()
{
	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Base"));
	BaseMesh->SetRelativeScale3D(FVector(2.f, 2.f, 0.2f));
	RootComponent = BaseMesh;

	OverlapComp = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComp"));
	OverlapComp->SetBoxExtent(FVector(48.f, 48.f, 32.f));
	OverlapComp->SetupAttachment(BaseMesh);
	
}

// Called when the game starts or when spawned
void ALaunchPad::BeginPlay()
{
	Super::BeginPlay();

	OverlapComp->OnComponentBeginOverlap.AddDynamic(this, &ALaunchPad::HandleOverlap);
}

void ALaunchPad::HandleOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	FVector LaunchPower = FVector(1000.f, 0.f, 1000.f);
	FVector Direction = RotateVectorDir(LaunchPower, GetActorRotation());
	
	AFPSCharacter* MyPawn = Cast<AFPSCharacter>(OtherActor);
	if (MyPawn != nullptr)
	{
		MyPawn->LaunchCharacter(Direction, true, false);
	}
	else
	{
		if (OtherComp && OtherComp->IsSimulatingPhysics())
		{
			OtherComp->AddForce(Direction*65.f, NAME_None, true);
		}
	}
}
