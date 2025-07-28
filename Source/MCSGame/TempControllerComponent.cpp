// Fill out your copyright notice in the Description page of Project Settings.


#include "TempControllerComponent.h"

// Sets default values
ATempControllerComponent::ATempControllerComponent()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ATempControllerComponent::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATempControllerComponent::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

