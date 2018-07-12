// Fill out your copyright notice in the Description page of Project Settings.

#include "MapMovementComponent.h"


// Sets default values for this component's properties
UMapMovementComponent::UMapMovementComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UMapMovementComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UMapMovementComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	AActor* Parrent = GetOwner();

	if (Parrent)
	{
		Parrent->SetActorLocation(Parrent->GetActorLocation() + FVector(Speed, 0.f, 0.f));
	}

	// ...
}

