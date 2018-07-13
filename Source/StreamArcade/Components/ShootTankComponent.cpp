// Fill out your copyright notice in the Description page of Project Settings.

#include "ShootTankComponent.h"
#include "Engine/World.h"
#include "TimerManager.h"

// Sets default values for this component's properties
UShootTankComponent::UShootTankComponent()
	:
	ShootPeriod(1.f)
{
	// ...
}


// Called when the game starts
void UShootTankComponent::BeginPlay()
{
	Super::BeginPlay();

	StartShooting();
}

void UShootTankComponent::Shoot()
{
	
	FActorSpawnParameters SpawnParameters;
	SpawnParameters.Owner = GetOwner();
	SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

// 	FVector SpawnLocation =
// 		GetOwner()->GetActorLocation()
// 		+
// 		GetOwner()->GetActorRotation().RotateVector(Offset);

	//FRotator SpawnRotation = GetOwner()->GetActorRotation();
	//SpawnRotation.Add(0.f, Angle, 0.f);

	AShootProjectile* Projectile = GetWorld()->SpawnActor<AShootProjectile>(ProjectileClass, Offset, Angle, SpawnParameters);
	if (Projectile) Projectile->Damage = Damage;
	
}


void UShootTankComponent::SetOffset(FVector NewOffset)
{
	Offset = NewOffset;
}

void UShootTankComponent::SetAngle(FRotator NewAngle)
{
	Angle = NewAngle;
}

void UShootTankComponent::StartShooting()
{
	GetWorld()->GetTimerManager().SetTimer(ShootingTimer, this, &UShootTankComponent::Shoot, ShootPeriod, true, ShootPeriod);
}

void UShootTankComponent::StopShooting()
{
	GetWorld()->GetTimerManager().ClearTimer(ShootingTimer);
}

