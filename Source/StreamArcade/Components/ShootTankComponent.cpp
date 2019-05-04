// Fill out your copyright notice in the Description page of Project Settings.

#include "ShootTankComponent.h"
#include "TankBarrel.h" //Add to set shoot point
#include "Engine/World.h"
#include "TimerManager.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UShootTankComponent::UShootTankComponent()
	:
	ShootPeriod(1.f)
{
	// ...
}

void UShootTankComponent::InitialiseBarrel(UTankBarrel * BarrelToSet) //Add to set shoot point
{
	Barrel = BarrelToSet;
}

// Called when the game starts
void UShootTankComponent::BeginPlay()
{
	Super::BeginPlay();

	StartShooting();
}

void UShootTankComponent::Shoot()
{

	if (FireSound != nullptr)
	{
		UGameplayStatics::PlaySoundAtLocation(this, FireSound, GetOwner()->GetActorLocation());
	}
	
	FActorSpawnParameters SpawnParameters;
	SpawnParameters.Owner = GetOwner();
	SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

// 	FVector SpawnLocation =
// 		GetOwner()->GetActorLocation()
// 		+
// 		GetOwner()->GetActorRotation().RotateVector(Offset);

	//FRotator SpawnRotation = GetOwner()->GetActorRotation();
	//SpawnRotation.Add(0.f, Angle, 0.f);

	if (Barrel != nullptr)
	{
		AShootProjectile* Projectile = GetWorld()->SpawnActor<AShootProjectile>(ProjectileClass, Barrel->GetSocketLocation(FName("Projectile")) + FVector(450.f,0.f, 0.f),
		Barrel->GetSocketRotation(FName("Projectile")), SpawnParameters);

		if (Projectile) Projectile->Damage = Damage;

		UE_LOG(LogTemp, Warning, TEXT("Shot tank: %s"), *(GetOwner()->GetName()));
	}
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


