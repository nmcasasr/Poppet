// Fill out your copyright notice in the Description page of Project Settings.


#include "Poppet_SpeedPad.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Poppet_Character.h"
#include <Engine/Engine.h>

// Sets default values
APoppet_SpeedPad::APoppet_SpeedPad()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	PlayerZoneColliderComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("PlayerZoneColliderComponent"));
	PlayerZoneColliderComponent->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	PlayerZoneColliderComponent->SetCollisionResponseToAllChannels(ECR_Ignore);
	PlayerZoneColliderComponent->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	RootComponent = PlayerZoneColliderComponent;
	PadComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Pad"));
	PadComponent->SetupAttachment(RootComponent);

	PadTag = "KeyB";
	bCanLaunch = true;
	launchPower = 1000;
}

// Called when the game starts or when spawned
void APoppet_SpeedPad::BeginPlay()
{
	Super::BeginPlay();
	PlayerZoneColliderComponent->OnComponentBeginOverlap.AddDynamic(this, &APoppet_SpeedPad::CheckKeyFromPlayer);
	PlayerZoneColliderComponent->OnComponentEndOverlap.AddDynamic(this, &APoppet_SpeedPad::StopPlayer);
}

void APoppet_SpeedPad::CheckKeyFromPlayer(UPrimitiveComponent * OverlappedComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	if (IsValid(OtherActor)) {
		APoppet_Character* OverlapedCharacter = Cast<APoppet_Character>(OtherActor);
		if (IsValid(OverlapedCharacter)) {
			LaunchPlayer(OverlapedCharacter);
			bCanLaunch = false;
		}
	}
}

void APoppet_SpeedPad::StopPlayer(UPrimitiveComponent * OverlappedComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex)
{
	if (IsValid(OtherActor)) {
		APoppet_Character* OverlapedCharacter = Cast<APoppet_Character>(OtherActor);
		if (IsValid(OverlapedCharacter)) {
			if (OverlapedCharacter->bIsUsingPowerUp) {
				return;
			}
			OverlapedCharacter->GetCharacterMovement()->MaxWalkSpeed = 400;
		}
	}
}

// Called every frame
void APoppet_SpeedPad::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APoppet_SpeedPad::LaunchPlayer(APoppet_Character * OtherActor)
{
	OtherActor->GetCharacterMovement()->MaxWalkSpeed = 2000;
}

