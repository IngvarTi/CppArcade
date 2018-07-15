// Fill out your copyright notice in the Description page of Project Settings.

#include "BonusHealth.h"
#include "Kismet/GameplayStatics.h"
#include "StreamArcadeGameModeBase.h"



void ABonusHealth::BonusCollected_Implementation()
{
	AStreamArcadeGameModeBase* Gamemode = Cast<AStreamArcadeGameModeBase>(UGameplayStatics::GetGameMode(this));
	if (!Gamemode) { return; }

	Gamemode->ChangeHealth(PickupPoints);
	UE_LOG(LogTemp, Log, TEXT("1 Health must be change on: %i"), PickupPoints);

	Super::BonusCollected_Implementation();
}


