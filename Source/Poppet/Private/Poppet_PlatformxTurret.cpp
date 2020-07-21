// Fill out your copyright notice in the Description page of Project Settings.


#include "Poppet_PlatformxTurret.h"

// Sets default values
APoppet_PlatformxTurret::APoppet_PlatformxTurret()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void APoppet_PlatformxTurret::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APoppet_PlatformxTurret::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APoppet_PlatformxTurret::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

