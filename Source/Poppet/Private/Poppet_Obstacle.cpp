// Fill out your copyright notice in the Description page of Project Settings.


#include "Poppet_Obstacle.h"

// Sets default values
APoppet_Obstacle::APoppet_Obstacle()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void APoppet_Obstacle::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APoppet_Obstacle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

