// Fill out your copyright notice in the Description page of Project Settings.


#include "Poppet_LaunchPad.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Poppet_Character.h"
#include <Engine/Engine.h>

// Sets default values
APoppet_LaunchPad::APoppet_LaunchPad()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	PlayerZoneColliderComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("PlayerZoneColliderComponent"));
	PlayerZoneColliderComponent->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	PlayerZoneColliderComponent->SetCollisionResponseToAllChannels(ECR_Ignore);
	PlayerZoneColliderComponent->SetCollisionResponseToChannel(ECC_Pawn,ECR_Overlap);
	RootComponent = PlayerZoneColliderComponent;
	PadComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Pad"));
	PadComponent->SetupAttachment(RootComponent);

	PadTag = "KeyA";
	bCanLaunch = false;
	launchPower = 1000;


}

// Called when the game starts or when spawned
void APoppet_LaunchPad::BeginPlay()
{
	Super::BeginPlay();
	PlayerZoneColliderComponent->OnComponentBeginOverlap.AddDynamic(this, &APoppet_LaunchPad::CheckKeyFromPlayer);
	
}

void APoppet_LaunchPad::CheckKeyFromPlayer(UPrimitiveComponent * OverlappedComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	if (IsValid(OtherActor)) {
		APoppet_Character* OverlapedCharacter = Cast<APoppet_Character>(OtherActor);
		if (IsValid(OverlapedCharacter)) {
				LaunchPlayer(OverlapedCharacter);
		}
	}
}


// Called every frame
void APoppet_LaunchPad::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APoppet_LaunchPad::LaunchPlayer(APoppet_Character * OtherActor)
{
	FVector LaunchVector = FVector::UpVector*launchPower;
	LaunchVector = FRotator(GetActorRotation()).RotateVector(LaunchVector);
	OtherActor->LaunchCharacter(LaunchVector, false, false);
	OtherActor->DeleteItem();
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Player enter the collision!"));
}

