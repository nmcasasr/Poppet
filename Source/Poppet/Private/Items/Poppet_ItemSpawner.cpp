// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/Poppet_ItemSpawner.h"
#include "Poppet_HealerBot.h"
#include "Components/StaticMeshComponent.h"
#include "Sound/SoundCue.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
APoppet_ItemSpawner::APoppet_ItemSpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MainMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	RootComponent = MainMeshComponent;

	bIsActive = false;

	MaxBotsCounter = 1;
	CurrentBotsCounter = 0;

	TimeToSpawn = 1.0f;

}

// Called when the game starts or when spawned
void APoppet_ItemSpawner::BeginPlay()
{
	Super::BeginPlay();
	
	GetWorld()->GetTimerManager().SetTimer(TimerHandle_Spawn, this, &APoppet_ItemSpawner::SpawnItem, TimeToSpawn, true);

	SpawnPoint = GetActorLocation();
}

void APoppet_ItemSpawner::SpawnItem()
{
	if (!bIsActive) {
		return;
	}

	if (CurrentBotsCounter >= MaxBotsCounter) {
		return;
	}
	if (IsValid(ItemClass)) {
		FActorSpawnParameters SpawnParameters;
		SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		APoppet_HealerBot* NewItem = GetWorld()->SpawnActor<APoppet_HealerBot>(ItemClass, SpawnPoint, FRotator::ZeroRotator, SpawnParameters);
		PlaySound();
		if (IsValid(NewItem)) {
			NewItem->SetSpawner(this);
			CurrentBotsCounter++;
		}
	}
}

// Called every frame
void APoppet_ItemSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APoppet_ItemSpawner::PlaySound()
{
	if (!IsValid(SpawnSound)) {
		UE_LOG(LogTemp, Warning, TEXT("Not valid Sound"));
		return;
	}
	UGameplayStatics::PlaySoundAtLocation(GetWorld(), SpawnSound, GetActorLocation());
}

