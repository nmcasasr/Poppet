// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/BoxComponent.h"
#include "Items/Poppet_ItemSpawner.h"
#include "Poppet_Character.h"
#include "..\..\Public\Items\Poppet_SpawnActivator.h"
#include <Engine/Engine.h>

// Sets default values
APoppet_SpawnActivator::APoppet_SpawnActivator()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ActivationZoneColliderComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("ActivationZoneColliderComponent"));
	ActivationZoneColliderComponent->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	ActivationZoneColliderComponent->SetCollisionResponseToAllChannels(ECR_Ignore);
	ActivationZoneColliderComponent->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	RootComponent = ActivationZoneColliderComponent;
}

// Called when the game starts or when spawned
void APoppet_SpawnActivator::BeginPlay()
{
	Super::BeginPlay();

	Spawner = Cast<APoppet_ItemSpawner>(ItemClass);
	ActivationZoneColliderComponent->OnComponentBeginOverlap.AddDynamic(this, &APoppet_SpawnActivator::ActivateSpawner);
	ActivationZoneColliderComponent->OnComponentEndOverlap.AddDynamic(this, &APoppet_SpawnActivator::DeactivateSpawner);
	
}

void APoppet_SpawnActivator::ActivateSpawner(UPrimitiveComponent * OverlappedComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	if (IsValid(OtherActor)) {
		APoppet_Character* OverlapedCharacter = Cast<APoppet_Character>(OtherActor);
		if (IsValid(OverlapedCharacter)) {
			if (IsValid(Spawner)) {
				Spawner->SetActive(true);
			}
		}
	}
}

void APoppet_SpawnActivator::DeactivateSpawner(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (IsValid(OtherActor)) {
		APoppet_Character* OverlapedCharacter = Cast<APoppet_Character>(OtherActor);
		if (IsValid(OverlapedCharacter)) {
			if (IsValid(Spawner)) {
				Spawner->SetActive(false);
			}
		}
	}
}

// Called every frame
void APoppet_SpawnActivator::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

