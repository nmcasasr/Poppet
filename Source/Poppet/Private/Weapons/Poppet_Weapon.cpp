// Fill out your copyright notice in the Description page of Project Settings.


#include "Poppet_Weapon.h"
#include "Poppet_Character.h"
#include "GameFramework/Character.h"

// Sets default values
APoppet_Weapon::APoppet_Weapon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void APoppet_Weapon::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APoppet_Weapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APoppet_Weapon::StartShooting()
{
	BP_StartShooting();
}

void APoppet_Weapon::StopShooting()
{
	BP_StopShooting();
}

void APoppet_Weapon::setCharacterOwner(ACharacter * NewOwner)
{
	if (IsValid(NewOwner))
	{
		SetOwner(NewOwner);
		CurrentOwnerCharacter = NewOwner;
	}

}

