// Fill out your copyright notice in the Description page of Project Settings.

#include "StreamArcadeGameModeBase.h"
#include "Engine/World.h"
#include "TimerManager.h"
#include "Kismet/GameplayStatics.h"
#include "Pawns/PlayerPawn.h"

#include "AI/Navigation/NavMeshBoundsVolume.h" // Add from TestingGrounds
#include "EngineUtils.h" // Add from TestingGrounds
#include "ActorPool.h" // Add from TestingGrounds

AStreamArcadeGameModeBase::AStreamArcadeGameModeBase():
	PlayerRecoverTime(3),
	CurrentShootLevel(-1),
	IncreaseDifficultyPeriod(4.f)
{
	EnemySpawnController = CreateDefaultSubobject<UEnemySpawnController>(TEXT("EnemySpawnController"));
	HealthsComponent = CreateDefaultSubobject<UGameHealthComponent>(TEXT("HealthsComponent"));

	NavMeshBoundsVolumePool = CreateDefaultSubobject<UActorPool>(FName("Nav Mesh Bounds Volume Pool")); // Add from TestingGrounds
}

void AStreamArcadeGameModeBase::BeginPlay()
{
	Super::BeginPlay();
	HealthsComponent->HealthsEnded.AddDynamic(this, &AStreamArcadeGameModeBase::EndGame);

	PlayerPawn = Cast<APlayerPawn>(UGameplayStatics::GetPlayerPawn(this, 0));
	if (!PlayerPawn) return;

	ChangeShootLevel(true);

	PlayerPawn->PawnDamaged.AddDynamic(this, &AStreamArcadeGameModeBase::ExplodePawn);

	GetWorld()->GetTimerManager().SetTimer(IncreaseDifficultyTimer, this, &AStreamArcadeGameModeBase::IncreaseDifficulty, IncreaseDifficultyPeriod, true);
}

void AStreamArcadeGameModeBase::ExplodePawn_Implementation()
{
	PlayerPawn->ExplodePawn();

	HealthsComponent->ChangeHealths(-1);

	ChangeShootLevel(false);

	if(!IsGameOver)
		GetWorld()->GetTimerManager().SetTimer(RecoverTimer, this, &AStreamArcadeGameModeBase::RecoverPawn, PlayerRecoverTime, false);
}

void AStreamArcadeGameModeBase::RecoverPawn_Implementation()
{
	PlayerPawn->RecoverPawn();
}

void AStreamArcadeGameModeBase::EndGame()
{
	IsGameOver = true;

	EnemySpawnController->SetActive(false);

	GameOver.Broadcast();

	UGameplayStatics::GetPlayerPawn(this, 0)->Destroy();

	UE_LOG(LogTemp, Log, TEXT("GAME OVER!!!"));

	SetPause(UGameplayStatics::GetPlayerController(this, 0)/*, false*/);
}

void AStreamArcadeGameModeBase::IncreaseDifficulty()
{
	EnemySpawnController->ChangeStageTimeMultiplier = FMath::Max(EnemySpawnController->ChangeStageTimeMultiplier * 0.95, 0.4);
	UE_LOG(LogTemp, Log, TEXT("Difficulty increased: %f"), EnemySpawnController->ChangeStageTimeMultiplier);
}

void AStreamArcadeGameModeBase::AddPoints(int Points)
{
	GamePoints += Points;
}

bool AStreamArcadeGameModeBase::ChangeShootLevel(bool Up)
{
	PlayerPawn = Cast<APlayerPawn>(UGameplayStatics::GetPlayerPawn(this, 0));
	if (!PlayerPawn) return false;

	int NewLevel = FMath::Clamp(CurrentShootLevel + (Up ? 1 : -1), 0, ShootInfoLevels.Num()-1);

	if (NewLevel == CurrentShootLevel) return false;

	CurrentShootLevel = NewLevel;

	PlayerPawn->ShootComponent->ShootInfos = ShootInfoLevels[CurrentShootLevel].ShootInfos;
	PlayerPawn->ShootComponent->ShootPeriod = ShootInfoLevels[CurrentShootLevel].ShootPeriod;

	return true;
}


void AStreamArcadeGameModeBase::ChangeHealth(int Health)
{
	HealthsComponent->ChangeHealths(Health);
	UE_LOG(LogTemp, Log, TEXT("2 Health must be change on: %i"), Health);
}

void AStreamArcadeGameModeBase::PopulateBoundsVolumePool() // Add from TestingGrounds
{
	auto VolumeIterator = TActorIterator<ANavMeshBoundsVolume>(GetWorld());
	while (VolumeIterator)
	{
		AddToPool(*VolumeIterator);
		++VolumeIterator;
	}
}


void AStreamArcadeGameModeBase::AddToPool(ANavMeshBoundsVolume *VolumeToAdd) // Add from TestingGrounds
{
	NavMeshBoundsVolumePool->Add(VolumeToAdd);
}
