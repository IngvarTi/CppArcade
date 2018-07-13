// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Actors/Projectiles/ShootProjectile.h"
#include "ShootTankComponent.generated.h"

USTRUCT(BlueprintType)
struct FShootTankInfo
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Shooting")
	TSubclassOf<AShootProjectile> ProjectileClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Shooting")
	float Damage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Shooting")
	FVector Offset;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Shooting")
	float Angle;

};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class STREAMARCADE_API UShootTankComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UShootTankComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	void Shoot();

	FTimerHandle ShootingTimer;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Shooting")
	TSubclassOf<AShootProjectile> ProjectileClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Shooting")
	float Damage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Shooting")
	FVector Offset;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Shooting")
	FRotator Angle;

public:	

	UFUNCTION(BlueprintCallable, Category = "Shooting")
	void SetOffset(FVector NewOffset);

	UFUNCTION(BlueprintCallable, Category = "Shooting")
	void SetAngle(FRotator NewAngle);

	UFUNCTION(BlueprintCallable, Category = "Shooting")
	void StartShooting();

	UFUNCTION(BlueprintCallable, Category = "Shooting")
	void StopShooting();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Shooting")
	float ShootPeriod;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Shooting")
	TArray<FShootTankInfo> ShootInfos;
	
};
