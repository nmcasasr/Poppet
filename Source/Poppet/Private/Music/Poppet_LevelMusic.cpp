// Fill out your copyright notice in the Description page of Project Settings.


#include "Poppet_LevelMusic.h"
#include "..\..\Public\Music\Poppet_LevelMusic.h"
#include "Components/BillboardComponent.h"
#include "Core/Poppet_GameMode.h"
#include "Components/AudioComponent.h"

// Sets default values
APoppet_LevelMusic::APoppet_LevelMusic()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MusicBillBoardComponent = CreateDefaultSubobject<UBillboardComponent>(TEXT("MusicBillBoardComponent"));
	RootComponent = MusicBillBoardComponent;

	MusicAudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("MusicAudioComponent"));
	MusicAudioComponent->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void APoppet_LevelMusic::BeginPlay()
{
	Super::BeginPlay();

	GameMmodeReference = Cast<APoppet_GameMode>(GetWorld()->GetAuthGameMode());
	if (IsValid(GameMmodeReference)) {
		GameMmodeReference->OnVictoryeDelegate.AddDynamic(this, &APoppet_LevelMusic::StopLevelMusic);
		GameMmodeReference->OnGameOverDelegate.AddDynamic(this, &APoppet_LevelMusic::StopLevelMusic);
	}
	
}

void APoppet_LevelMusic::StopLevelMusic()
{
	MusicAudioComponent->Stop();
}

