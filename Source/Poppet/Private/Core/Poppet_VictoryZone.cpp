// Fill out your copyright notice in the Description page of Project Settings.


#include "Poppet_VictoryZone.h"
#include "Components/BoxComponent.h"
#include "..\..\Public\Core\Poppet_VictoryZone.h"
#include "Poppet_Character.h"
#include "Core/Poppet_GameMode.h"

// Sets default values
APoppet_VictoryZone::APoppet_VictoryZone()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	VictoryZoneComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("VicotoryZoneComponent"));
	RootComponent = VictoryZoneComponent;
	VictoryZoneComponent->SetBoxExtent(FVector(100.0f));
}

// Called when the game starts or when spawned
void APoppet_VictoryZone::BeginPlay()
{
	Super::BeginPlay();

	GameModeReference = Cast<APoppet_GameMode>(GetWorld()->GetAuthGameMode());
	
}

// Called every frame
void APoppet_VictoryZone::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APoppet_VictoryZone::NotifyActorBeginOverlap(AActor * OtherActor)
{
	if (IsValid(OtherActor) && IsValid(GameModeReference))
	{
		APoppet_Character* Poppet_Character = Cast<APoppet_Character>(OtherActor);
		if (IsValid(Poppet_Character))
		{
			GameModeReference->Victory(Poppet_Character);
		}
	}
}

