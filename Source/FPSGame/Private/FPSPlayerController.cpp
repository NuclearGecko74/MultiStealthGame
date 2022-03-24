// Fill out your copyright notice in the Description page of Project Settings.


#include "FPSPlayerController.h"

void AFPSPlayerController::ChangeMap(FString URL)
{
	ClientTravel(URL, ETravelType::TRAVEL_Absolute);
}
