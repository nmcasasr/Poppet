// Fill out your copyright notice in the Description page of Project Settings.


#include "Poppet_PowerUp.h"
#include "..\..\Public\Items\Poppet_PowerUp.h"
#include "Components/StaticMeshComponent.h"
#include "Poppet_Character.h"

APoppet_PowerUp::APoppet_PowerUp()
{
	PowerUp_MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PowerUpMeshComponent"));
	PowerUp_MeshComponent->SetupAttachment(RootComponent);
	PowerUp_MeshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void APoppet_PowerUp::Pickup(APoppet_Character * PickUpActor)
{
	Super::Pickup(PickUpActor);
	PickUpActor->GainPowerUp();
	Destroy();
}
