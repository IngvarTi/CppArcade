// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actors/Bonuses/Bonus.h"
#include "BonusHealth.generated.h"

/**
 * 
 */
UCLASS()
class STREAMARCADE_API ABonusHealth : public ABonus
{
	GENERATED_BODY()

public:
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Bonus")
	int PickupPoints;
	
protected:

	virtual void BonusCollected_Implementation() override;
};
