// Fill out your copyright notice in the Description page of Project Settings.


#include "Poppet_Launch_Pad_Key.h"
#include "..\..\Public\Items\Poppet_Launch_Pad_Key.h"
#include "Components/StaticMeshComponent.h"
#include "Poppet_Character.h"
APoppet_Launch_Pad_Key::APoppet_Launch_Pad_Key()
{
	Launch_Pad_KeyMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("KeyMeshComponent"));
	Launch_Pad_KeyMeshComponent->SetupAttachment(RootComponent);
	Launch_Pad_KeyMeshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	KeyTag = "KeyA";
}

void APoppet_Launch_Pad_Key::Pickup(APoppet_Character* PickUpActor)
{
	Super::Pickup(PickUpActor);

	PickUpActor->AddItem(KeyTag);
	Destroy();
}
